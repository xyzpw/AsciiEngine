#pragma once

#include <functional>
#include <unordered_map>
#include "AsciiEngine/core/component.hpp"

namespace AsciiEngine
{
	enum class MovementControlType {
		None,
		WASD,
		ArrowKeys,
		Vim,
	};

	struct Controller : Component {
		int id;
		std::unordered_map<int, std::function<void()>> keyFunctionMap;

		Controller() {}

		/*
		 * @key: trigger key
		 * @call: the function called if the key is pressed
		 */
		void addKey(int key, std::function<void()> call)
		{
			keyFunctionMap[key] = call;
		}
	};
}
