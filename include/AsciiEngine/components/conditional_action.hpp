#pragma once

#include "AsciiEngine/core/component.hpp"
#include <functional>
#include <optional>

namespace AsciiEngine
{
	/*
	 * Can be used to run a function if a condition is met.
	 * If no condition is given, it will always be true.
	 */
	struct ConditionalAction : Component {
		std::function<void()> actionFn;
		std::optional<std::function<bool()>> conditionFn;

		ConditionalAction(std::function<void()> action, std::function<bool()> condition)
			: actionFn(action), conditionFn(condition) {}
		ConditionalAction(std::function<void()> action)
			: actionFn(action), conditionFn(std::nullopt) {}
		ConditionalAction() {}

		void setAction(std::function<void()> call) { actionFn = call; }
		void setCondition(std::function<bool()> call)
			{ conditionFn = call; }

		/*
		 * Try to execute action.
		 *
		 * return: true if the action was called
		 */
		bool tryExecute()
		{
			if (!actionFn)
				return false;

			bool hasValue = conditionFn.has_value();

			if (!hasValue || (hasValue && conditionFn.value()() == true)) {
				actionFn();
				return true;
			}

			return false;
		}
	};
}
