#pragma once

#include <functional>
#include <vector>

namespace AsciiEngine
{
	template<typename... Args>
	struct Signal {
		using Slot = std::function<void(Args...)>;

		void connect(const Slot &slot)
		{
			slots.push_back(slot);
		}

		void emit(Args... args)
		{
			for (auto &sl : slots)
				sl(args...);
		}

		Signal() {}

	private:
		std::vector<Slot> slots;
	};
}
