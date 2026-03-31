#pragma once

#include "AsciiEngine/core/component.hpp"
#include "AsciiEngine/core/mouse_state.hpp"

namespace AsciiEngine
{
	struct Clickable : Component {
		virtual void onMouseDown(const MouseState&) {}
		virtual void onMouseUp(const MouseState&) {}
		virtual void onHold(const MouseState&) {}
	};
}
