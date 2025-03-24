#include <stdio.h>
#include <stdarg.h>
#include "LogManager.h"
#include "../utility.h"

namespace df {

	LogManager::LogManager() {
		setType("LogManager");
		m_log_level = 1;
		m_do_flush = false;
		m_log_time_string = true;
		m_log_step_count = false;
		m_p_f = nullptr;
	}

	LogManager& LogManager::getInstance() {
		static LogManager single;
		return single;
	}

	LogManager::~LogManager() {
		shutDown();
	}

	int LogManager::startUp() {
		Manager::startUp();

		fopen_s(&m_p_f, LOGFILE_NAME.c_str(), "w");

		if (m_p_f != nullptr) return 0;
		else return -1;
	}

	void LogManager::shutDown() {
		Manager::shutDown();

		if (m_p_f != nullptr) fclose(m_p_f);
	}

	// Set whether to flush after every log write.
	void LogManager::setFlush(bool do_flush) {
		m_do_flush = do_flush;
	}

	// Write message to console.
	int LogManager::writeLog(const char* fmt, ...) const {
		return writeLog(INT_MAX, fmt);
	}

	// Write message to console.
	int LogManager::writeLog(int log_level, const char* fmt, ...) const {
		if (log_level < m_log_level) return -1;

		int bytes = 0;

		va_list args;
		va_start(args, fmt);

		if (m_log_time_string) {	// Print timestamp
			fprintf(m_p_f, "[");
			char* timeString = utility::getTimeString();
			fprintf(m_p_f, timeString);
			fprintf(m_p_f, "] ");
		}
		if (m_log_step_count) {	// Print num. game loops
			// TODO: Implement game loop string
		}

		bytes = vfprintf(m_p_f, fmt, args);
		fprintf(m_p_f, "\n");

		va_end(args);

		if (m_do_flush) fflush(m_p_f);

		if (bytes > 0) return bytes;
		else return -1;
	}
}