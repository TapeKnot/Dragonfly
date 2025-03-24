#include "TestReticle.h"
#include "../Managers/DisplayManager.h"
#include "../Events/EventMouse.h"
#include "../Managers/GameManager.h"
#include "../Managers/WorldManager.h"

namespace df {

	TestReticle::TestReticle() {
		setType("Reticle");
		setSolidness(SPECTRAL);
	}

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int TestReticle::eventHandler(const Event* p_e) {
		if (p_e->getType() == MSE_EVENT) {
			const EventMouse* p_mouse_event = dynamic_cast <const EventMouse*> (p_e);
			mse(p_mouse_event);

			return 1;
		}

		return 0;
	}

	void TestReticle::mse(const EventMouse* p_mouse_event) {

		WM.moveObject(this, p_mouse_event->getMousePosition());
	}

	int TestReticle::draw() {
		return DM.drawCh(getPosition(), '+', GREEN);
	}
}