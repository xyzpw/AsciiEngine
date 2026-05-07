#include "AsciiEngine/core/stopwatch.hpp"
#include <chrono>

namespace AsciiEngine
{
	Stopwatch::Stopwatch(bool autostart)
	{
		if (autostart)
			start();
	}

	void Stopwatch::start()
	{
		if (active)
			return;

		startTime = steady::now();
		active = true;
	}

	void Stopwatch::stop()
	{
		if (!active)
			return;

		active = false;

		stopTime = steady::now();
		completionTimeMs = elapsedMs();
	}

	void Stopwatch::clear()
	{
		startTime = steady::now();
		stopTime = steady::now();
		completionTimeMs = 0;
	}

	void Stopwatch::restart()
	{
		if (active)
			stop();

		clear();
		start();
	}

	float Stopwatch::elapsed() const
	{
		using std::chrono::duration;

		float t = duration<float>(steady::now() - startTime).count();
		return t;
	}

	int Stopwatch::elapsedMs() const
	{
		float dur = elapsed();
		return dur * 1000;
	}
}
