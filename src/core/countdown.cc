#include "AsciiEngine/core/countdown.hpp"
#include <chrono>

using std::chrono::duration_cast;

namespace AsciiEngine
{
	Countdown::Countdown(float seconds, bool autostart)
	{
		initialTime = seconds;

		if (autostart)
			start();
	}

	void Countdown::start()
	{
		if (isActive() || isComplete())
			return;

		paused = false;

		if (!started) {
			reset();
			started = true;
		}
	}

	void Countdown::pause()
	{
		paused = true;
		pauseTime = steady::now();
	}

	void Countdown::reset()
	{
		paused = false;
		started = false;

		using std::chrono::duration;

		auto t = duration<float>(initialTime);
		endTime = steady::now() + duration_cast<steady::duration>(t);
	}

	void Countdown::restart()
	{
		reset();
		start();
	}

	void Countdown::restart(float seconds)
	{
		initialTime = seconds;

		reset();
		start();
	}

	void Countdown::setInitialTime(float seconds)
	{
		initialTime = seconds;
	}

	float Countdown::timeLeft()
	{
		if (!started)
			return initialTime;

		using std::chrono::duration;

		auto now = paused ? pauseTime : steady::now();
		float t = duration<float>(endTime - now).count();

		if (t <= 0)
			t = 0;

		return t;
	}

	bool Countdown::isComplete()
	{
		return timeLeft() == 0;
	}

	bool Countdown::isActive()
	{
		return started && !paused;
	}
}
