#pragma once
#ifndef __CLOCK_H__
#define __CLOCK_H__

namespace df {

	class Clock {
	private:
		long int m_previous_time;	// Previous time delta() called (in microsec).

	public:
		// Sets previous_time to current time.
		Clock();

		// Return time elapsed since delta() was last called, -1 if error.
		// Resets previous time.
		// Units are in milliseconds.
		long int delta();

		// Return time elapsed since delta() was last called, -1 if error.
		// Does not reset previous time.
		// Units are in milliseconds.
		long int split() const;

		//long int toMicroseconds(SYSTEMTIME sys_time);
	};

}

#endif