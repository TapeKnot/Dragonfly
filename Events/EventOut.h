#pragma once
#ifndef __EVENTOUT_H__
#define __EVENTOUT_H__
#include "Event.h"

namespace df {

	const std::string OUT_EVENT = "df::out";

	class EventOut : public Event {

	private:

	public:
		EventOut();
	};
}

#endif