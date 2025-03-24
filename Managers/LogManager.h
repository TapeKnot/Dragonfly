#pragma once
#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__
#define LM df::LogManager::getInstance()
#include <stdio.h>
#include "Manager.h"

namespace df {

	const std::string LOGFILE_NAME = "dragonfly.log";

	class LogManager : public Manager {
	private:
		LogManager();						// No constructing.
		LogManager(LogManager const&);		// No copying.
		void operator=(LogManager const&);	// No assigning.

		bool m_do_flush;
		FILE* m_p_f;

		int m_log_level;
		bool m_log_time_string;
		bool m_log_step_count;
		
	public:
		~LogManager();
		static LogManager& getInstance();
		int startUp();
		void shutDown();
		void setFlush(bool do_flush = true);
		int writeLog(const char* fmt, ...) const;
		int writeLog(int log_level, const char *fmt, ...) const;
	};

}

#endif