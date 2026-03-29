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
		MouseButton button;
		MouseAction action;
		Math::Vector2 position;

		void reset()
		{
			button = MouseButton::NONE;
			action = MouseAction::NONE;
			position.x = 0;
			position.y = 0;
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
