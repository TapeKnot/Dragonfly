#pragma once
#ifndef __TESTRETICLE_H__
#define __TESTRETICLE_H__
#include "../Object.h"
#include "../Events/EventMouse.h"

namespace df {

	class TestReticle : Object {

	private:

	public:
		TestReticle();
		int eventHandler(const Event* p_e);
		void mse(const EventMouse* p_mouse_event);
		int draw();
	};

}

#endif