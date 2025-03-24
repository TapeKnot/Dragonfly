#include "Event.h"

namespace df {

	// Create base event.
	Event::Event() {
		m_event_type = UNDEFINED_EVENT;
	}

	// Destructor.
	Event::~Event() {

	}

	// Set event type.
	void Event::setType(std::string new_type) {
		m_event_type = new_type;
	}

	// Get event type.
	std::string Event::getType() const {
		return m_event_type;
	}
}