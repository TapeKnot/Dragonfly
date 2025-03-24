#pragma once
#ifndef __TESTMOVEOBJECT_H__
#define __TESTMOVEOBJECT_H__
#include "../Object.h"
#include "../Events/EventKeyboard.h"

namespace df {

	//int DEFAULT_MOVE_SLOWDOWN = 5;

	class TestMoveObject : Object {

	private:
		int move_slowdown;
		int move_countdown;

	public:
		TestMoveObject();
		int eventHandler(const Event* p_e);
		void kbd(const EventKeyboard* p_keyboard_event);
		void move(Vector velocity);
		int draw();
	};

}

#endif