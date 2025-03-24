#include "EventKeyboard.h"

namespace df {

	// Default constructor.
	EventKeyboard::EventKeyboard() {
		setType(KEYBOARD_EVENT);
	}

	// Set key in event.
	void EventKeyboard::setKey(Keyboard::Key new_key) {
		m_key_val = new_key;
	}

	// Get key from event.
	Keyboard::Key EventKeyboard::getKey() const {
		return m_key_val;
	}

	// Set keyboard event action.
	void EventKeyboard::setKeyboardAction(EventKeyboardAction new_action) {
		m_keyboard_action = new_action;
	}

	// Get keyboard event action.
	EventKeyboardAction EventKeyboard::getKeyboardAction() const {
		return m_keyboard_action;
	}
}