#pragma once

#include <string>
#include <vector>
#include <cstdarg>

namespace AsciiEngine
{
	enum class LogLevel {
		NONE,
		LOG,
		WARN,
		ERROR,
		SUCCESS,
	};

	struct LogEntry {
		LogLevel level;
		std::string message() const;

		LogEntry(LogLevel level, std::string text)
			: level(level), text(text) {}

	private:
		std::string text;

	};

	struct Debug {
		void log(const char *fmt, ...);
		void success(const char *fmt, ...);
		void warn(const char *fmt, ...);
		void error(const char *fmt, ...);
		void print(const char *fmt, ...);

		void printLogs();

		int errors = 0;
		int warnings = 0;
	private:
		std::vector<std::string> logs;
		std::vector<LogEntry> logEntries;

		void logInternal(LogLevel level, const char* fmt, va_list);
	};
}
