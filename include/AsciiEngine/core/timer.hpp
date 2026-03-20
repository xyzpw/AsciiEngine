#pragma once

#include <chrono>

namespace AsciiEngine
{
	/* can be used to time stuff */
	struct Timer {
		bool active = false;
		int completionTimeMs;

		// @autostart: start automatically if true
		Timer(bool autostart = false);

		// start timer if not started yet
		void start();
		void stop();
		void clear();
		// clear all values and start the timer
		void restart();

		// return: chrono duration since the timer was started
		std::chrono::duration<float> elapsed() const;
		// return: milliseconds since the timer was started
		int elapsedMs();

	private:
		using steady = std::chrono::steady_clock;

		std::chrono::time_point<steady> startTime;
		std::chrono::time_point<steady> stopTime;
	};
}
