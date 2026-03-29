#pragma once

#include "AsciiEngine/math/vector2.hpp"

namespace AsciiEngine
{
	enum class MouseButton {
		NONE,
		LEFT,
		MIDDLE,
		RIGHT,
	};

	enum class MouseAction {
		NONE,
		PRESS,
		RELEASE,
	};

	struct MouseEvent {
		MouseButton button = MouseButton::NONE;
		MouseAction action = MouseAction::NONE;
		Math::Vector2 position{0, 0};

		void reset()
		{
			button = MouseButton::NONE;
			action = MouseAction::NONE;
			position.x = 0;
			position.y = 0;
		}

		operator bool() const
		{
			return action != MouseAction::NONE;
		}
	};

	struct MouseState {
		Math::Vector2 position;
		MouseButton button = MouseButton::NONE;
		float holdTime = 0;

		bool isDown() const { return button != MouseButton::NONE; }

		void reset()
		{
			position.x = 0;
			position.y = 0;
			button = MouseButton::NONE;
			holdTime = 0;
		}
	};
}
