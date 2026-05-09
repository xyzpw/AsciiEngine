#pragma once

#include <chrono>

namespace AsciiEngine
{
	struct Countdown {
		/*
		 * @autostart: start automatically if true
		 */
		Countdown(float seconds = 0, bool autostart = false);

		void start();
		void pause();
		void reset();

		/*
		 * start the countdown from the beginning
		 */
		void restart();

		/*
		 * start the countdown from the beginning
		 * @seconds: new initial time
		 */
		void restart(float seconds);

		/*
		 * set the initial countdown time
		 */
		void setInitialTime(float seconds);

		float getInitialTime() { return initialTime; }

		/*
		 * return: seconds until countdown has finished
		 */
		float timeLeft();

		/*
		 * return: true if the timer has started and is finished
		 */
		bool isComplete();

		bool isStarted() { return started; }
		bool isPaused() { return paused; }

		/*
		 * return: true if timer is currently counting
		 */
		bool isActive();

	private:
		using steady = std::chrono::steady_clock;

		steady::time_point endTime;
		steady::time_point pauseTime;

		float initialTime = 0;
		bool started = false;
		bool paused = false;
	};
}
