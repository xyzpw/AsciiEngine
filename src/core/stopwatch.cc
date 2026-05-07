#include "AsciiEngine/core/timer.hpp"
#include <chrono>

namespace AsciiEngine
{
	Timer::Timer(bool autostart)
	{
		if (autostart)
			start();
	}

	void Timer::start()
	{
		if (active)
			return;

		startTime = steady::now();
		active = true;
	}

	void Timer::stop()
	{
		if (!active)
			return;

		active = false;

		stopTime = steady::now();
		completionTimeMs = elapsedMs();
	}

	void Timer::clear()
	{
		startTime = steady::now();
		stopTime = steady::now();
		completionTimeMs = 0;
	}

	void Timer::restart()
	{
		if (active)
			stop();

		clear();
		start();
	}

	float Timer::elapsed() const
	{
		using std::chrono::duration;

		float t = duration<float>(steady::now() - startTime).count();
		return t;
	}

	int Timer::elapsedMs() const
	{
		float dur = elapsed();
		return dur * 1000;
	}
}
