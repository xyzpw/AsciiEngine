#pragma once

#include <chrono>

namespace AsciiEngine
{
	/* can be used to time stuff */
	struct Stopwatch {
		bool active = false;
		int completionTimeMs;

		// @autostart: start automatically if true
		Stopwatch(bool autostart = false);

		// start timer if not started yet
		void start();
		void stop();
		void clear();
		// clear all values and start the timer
		void restart();

		// return: seconds since the timer was started
		float elapsed() const;
		// return: milliseconds since the timer was started
		int elapsedMs() const;

	private:
		using steady = std::chrono::steady_clock;

		std::chrono::time_point<steady> startTime;
		std::chrono::time_point<steady> stopTime;
	};
}
