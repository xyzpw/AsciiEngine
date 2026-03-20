#pragma once

#include <functional>

namespace AsciiEngine
{
	struct KeyAction {
		int key;
		std::function<void()> action;

		KeyAction(int k, std::function<void()> call)
			: key(k), action(call) {}
	};
}
