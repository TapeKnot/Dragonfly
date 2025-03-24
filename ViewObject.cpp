#include "ViewObject.h"
#include "Managers/WorldManager.h"
#include "Managers/LogManager.h"
#include "Managers/DisplayManager.h"
#include "Testing/Testing.h"
#include "utility.h"
#include "Events/EventView.h"

namespace df {

	// Construct ViewObject.
	// Object settings: SPECTRAL, max alt.
	// ViewObject defaults: border, top_center, default color, draw_value.
	ViewObject::ViewObject() {

		// Initialize Object attributes.
		setSolidness(SPECTRAL);
		setAltitude(MAX_ALTITUDE);
		setType("ViewObject");

		// Initialize ViewObject attributes.
		setValue(0);
		setDrawValue();
		setBorder(true);
		setLocation(TOP_CENTER);
		setColor(COLOR_DEFAULT);
	}

	// Draw view string and value.
	int ViewObject::draw() {

		std::string temp_str = "";

		// Display view_string + value.
		if (m_border)
			temp_str = " " + getViewString() + " " + utility::toString(m_value) + " ";
		else
			temp_str = getViewString() + " " + utility::toString(m_value);

		// Draw centered at position.
		Vector pos = utility::viewToWorld(getPosition());
		DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());

		if (m_border) {
			// TODO: Draw box around display.
		}

		return 0;
	}

	// Handle 'view' event if tag matches view_string (others ignored).
	// Return 0 if ignored, else 1 if handled.
	int ViewObject::eventHandler(const Event* p_e) {
		
		// See if this is 'view' event.
		if (p_e->getType() == VIEW_EVENT) {
			const EventView* p_ve = dynamic_cast <const EventView*> (p_e);

			// See if this event is meant for this object.
			if (p_ve->getTag() == getViewString()) {
				if (p_ve->getDelta())
					setValue(getValue() + p_ve->getValue());	// Change in value.
				else
					setValue(p_ve->getValue());					// New value.

				// Event was handled, return ok.
				return 1;
			}
		}

		// If here, event was not handled. Call parent eventHandler().
		return Object::eventHandler(p_e);
	}

	// Set general location of ViewObject on screen.
	void ViewObject::setLocation(ViewObjectLocation new_location) {
		Vector p;
		int y_delta = 0;


		// Set new position based on location.
		switch (new_location) {
			case TOP_LEFT:
				p.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
				if (!getBorder())
					y_delta = -1;
				break;
			case TOP_CENTER:
				p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
				if (!getBorder())
					y_delta = -1;
				break;
			case TOP_RIGHT:
				p.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
				if (!getBorder())
					y_delta = -1;
				break;
			case CENTER_LEFT:
				p.setXY(WM.getView().getHorizontal() * 1 / 6, (WM.getView().getVertical() / 2) - 1);
				break;
			case CENTER_CENTER:
				p.setXY(WM.getView().getHorizontal() * 3 / 6, (WM.getView().getVertical() / 2) - 1);
				break;
			case CENTER_RIGHT:
				p.setXY(WM.getView().getHorizontal() * 5 / 6, (WM.getView().getVertical() / 2) - 1);
				break;
			case BOTTOM_LEFT:
				p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() - 1);
				if (!getBorder())
					y_delta = 1;
				break;
			case BOTTOM_CENTER:
				p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() - 1);
				if (!getBorder())
					y_delta = 1;
				break;
			case BOTTOM_RIGHT:
				p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() - 1);
				if (!getBorder())
					y_delta = 1;
				break;
			default:
				printf("\tERROR\t: ViewObject.setLocation() - Invalid ViewObjectLocation.\n");
				LM.writeLog(ts::TEST_LOG_LEVEL, "\tERROR\t: ViewObject.setLocation() - Invalid ViewObjectLocation.\n");
				break;
		}

		// Shift, as needed, based on border.
		p.setY(p.getY() + y_delta);

		// Set position of object to new position.
		setPosition(p);

		// Set new location.
		m_location = new_location;
	}

	// Get general location of ViewObject on screen.
	ViewObjectLocation ViewObject::getLocation() const {
		return m_location;
	}

	// Set view value.
	void ViewObject::setValue(int new_value) {
		m_value = new_value;
	}

	// Get view value.
	int ViewObject::getValue() const {
		return m_value;
	}

	// Set view border (true = display border).
	void ViewObject::setBorder(bool new_border) {

		if (m_border != new_border) {
			m_border = new_border;

			// Reset location to account for border setting.
			setLocation(getLocation());
		}
	}

	// Get view border (true = display border).
	bool ViewObject::getBorder() const {
		return m_border;
	}

	// Set view color.
	void ViewObject::setColor(Color new_color) {
		m_color = new_color;
	}

	// Get view color.
	Color ViewObject::getColor() const {
		return m_color;
	}

	// Set view display string.
	void ViewObject::setViewString(std::string new_view_string) {
		m_view_string = new_view_string;
	}

	// Get view display string.
	std::string ViewObject::getViewString() const {
		return m_view_string;
	}

	// Set true to draw value with display string.
	void ViewObject::setDrawValue(bool new_draw_value) {
		m_draw_value = new_draw_value;
	}

	// Get draw value (true if draw value with display string).
	bool ViewObject::getDrawValue() const {
		return m_draw_value;
	}
}