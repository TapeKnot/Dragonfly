#include "TestMoveObject.h"
#include "../Managers/DisplayManager.h"
#include "../Events/EventKeyboard.h"
#include "../Managers/GameManager.h"
#include "../Events/EventStep.h"
#include "../Managers/WorldManager.h"
#include "../Events/EventOut.h"

namespace df {

	TestMoveObject::TestMoveObject() {
		//int move_slowdown = DEFAULT_MOVE_SLOWDOWN;
		move_slowdown = 5;
		move_countdown = move_slowdown;
	}

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int TestMoveObject::eventHandler(const Event* p_e) {
		if (p_e->getType() == KEYBOARD_EVENT) {
			const EventKeyboard* p_keyboard_event = dynamic_cast <const EventKeyboard*> (p_e);
			kbd(p_keyboard_event);

			return 1;
		}
		else if (p_e->getType() == STEP_EVENT) {
			move_countdown--;
			if (move_countdown < 0) move_countdown = 0;

			return 1;
		}
		else if (p_e->getType() == OUT_EVENT) {
			GM.setGameOver();

			return 1;
		}

		return 0;
	}

	void TestMoveObject::kbd(const EventKeyboard* p_keyboard_event) {

		switch (p_keyboard_event->getKey()) {
		case Keyboard::ESCAPE:	// Quit
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				GM.setGameOver();
			break;
		case df::Keyboard::W:	// Up
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				move(Vector(0,-1));
			break;
		case df::Keyboard::A:	// Left
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				move(Vector(-1, 0));
			break;
		case df::Keyboard::S:	// Down
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				move(Vector(0, 1));
			break;
		case df::Keyboard::D:	// Right
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				move(Vector(1, 0));
			break;
		}
	}

	void TestMoveObject::move(Vector direction) {
		// Check if time to move.
		if (move_countdown > 0) return;

		move_countdown = move_slowdown;

		WM.moveObject(this, getPosition() + direction);
	}

	int TestMoveObject::draw() {
		return DM.drawCh(getPosition(), 'M', YELLOW);
	}
}