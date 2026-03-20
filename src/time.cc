#include "AsciiEngine/engine.hpp"
#include <functional>
#include <thread>
#include <chrono>

namespace AsciiEngine
{
	void Engine::setTickInterval(int ms)
	{
		TICK_INTERVAL_MS = ms;
	}

	void Engine::runAfterFrame(std::function<void()> call)
	{
		if (!call)
			return;

		std::thread([this, call]() {
			while (currentlyInFrame) {
				std::this_thread::yield();
			}

			call();
		}).detach();
	}

	void Engine::runAfterSeconds(float seconds, std::function<void()> call)
	{
		if (!call)
			return;

		auto sleepTime = std::chrono::duration<float>(seconds);
		std::thread([this, call, sleepTime]() {
			std::this_thread::sleep_for(sleepTime);
			call();
		}).detach();
	}
}
