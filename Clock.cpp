#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>
#include "Clock.h"

namespace df {

	Clock::Clock() {
		SYSTEMTIME sys_time;
		GetSystemTime(&sys_time);

		m_previous_time = (sys_time.wDay * 24 * 60 * 60 * 10000)
			+ (sys_time.wHour * 60 * 60 * 10000)
			+ (sys_time.wMinute * 60 * 10000)
			+ (sys_time.wSecond * 10000)
			+ (sys_time.wMilliseconds);
	}

	long int Clock::delta() {
		SYSTEMTIME sys_time;
		GetSystemTime(&sys_time);
		long int current_time = (sys_time.wDay * 24 * 60 * 60 * 10000)
			+ (sys_time.wHour * 60 * 60 * 10000)
			+ (sys_time.wMinute * 60 * 10000)
			+ (sys_time.wSecond * 10000)
			+ (sys_time.wMilliseconds);

		long int elapsed_time = current_time - m_previous_time;
		m_previous_time = current_time;

		return elapsed_time;
	}

	long int Clock::split() const {
		SYSTEMTIME sys_time;
		GetSystemTime(&sys_time);
		long int current_time = (sys_time.wDay * 24 * 60 * 60 * 10000)
			+ (sys_time.wHour * 60 * 60 * 10000)
			+ (sys_time.wMinute * 60 * 10000)
			+ (sys_time.wSecond * 10000)
			+ (sys_time.wMilliseconds);

		long int elapsed_time = current_time - m_previous_time;

		/*if (elapsed_time > 100) {
			printf("ERROR\n");
		}*/

		return elapsed_time;
	}

	//// Convert SYSTEMTIME to microseconds (long int)
	//long int Clock::toMicroseconds(SYSTEMTIME sys_time) {
	//	return (sys_time.wDay * 24 * 60 * 60 * 10000000)
	//		+ (sys_time.wHour * 60 * 60 * 10000000)
	//		+ (sys_time.wMinute * 60 * 10000000)
	//		+ (sys_time.wSecond * 10000000)
	//		+ (sys_time.wMilliseconds * 1000);
	//}
}