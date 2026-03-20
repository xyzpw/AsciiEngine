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

	std::chrono::duration<float> Timer::elapsed() const
	{
		return std::chrono::duration<float>(steady::now() - startTime);
	}

	int Timer::elapsedMs()
	{
		auto dur = elapsed();
		return std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	}
}
