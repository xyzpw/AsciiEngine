#include "AsciiEngine/core/debug.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/math/ray.hpp"
#include <cstdarg>
#include <iostream>
#include <format>
#include <ncurses.h>

#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_RESET "\x1b[0m"

using namespace AsciiEngine::Math;

namespace AsciiEngine
{
	std::string LogEntry::message() const
	{
		switch (level) {
		case LogLevel::LOG:
			return "[LOG] " + text;
		case LogLevel::WARN:
			return std::format("{}[WARN] {}{}", ANSI_YELLOW,
					   text, ANSI_RESET);
		case LogLevel::ERROR:
			return std::format("{}[ERROR] {}{}", ANSI_RED, text,
					   ANSI_RESET);
		case LogLevel::SUCCESS:
			return std::format("{}[OK] {}{}", ANSI_GREEN, text,
					   ANSI_RESET);
		default:
			return text;
		}
	}

	void Debug::log(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		logInternal(LogLevel::LOG, fmt, args);
		va_end(args);
	}

	void Debug::success(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		logInternal(LogLevel::SUCCESS, fmt, args);
		va_end(args);
	}

	void Debug::warn(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		logInternal(LogLevel::WARN, fmt, args);
		va_end(args);
		++warnings;
	}

	void Debug::error(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		logInternal(LogLevel::ERROR, fmt, args);
		va_end(args);
		++errors;
	}

	void Debug::print(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		logInternal(LogLevel::NONE, fmt, args);
		va_end(args);
	}

	void Debug::drawLine(const Ray &ray, float distance)
	{
		const auto &[point, direction] = ray;

		for (int i = 0; i < distance; ++i) {
			Vector2 p = point + direction * i;
			mvprintw(p.y, p.x, ".");
		}
	}

	void Debug::printLogs()
	{
		for (const auto &ent : logEntries) {
			std::cout << ent.message() << "\n";
		}
	}

	void Debug::logInternal(LogLevel level, const char* fmt, va_list args)
	{
		char buffer[1024];

		va_list argsCopy;
		va_copy(argsCopy, args);

		vsnprintf(buffer, sizeof(buffer), fmt, argsCopy);

		va_end(argsCopy);

		logEntries.emplace_back(level, buffer);
	}
}
