#pragma once

#include "AsciiEngine/math/vector2.hpp"

namespace AsciiEngine::Math
{
	struct Bounds {
		Vector2 position;
		Vector2 size;

		Vector2 center() const
		{
			return { left() + size.x * 0.5f,
				 top() + size.y * 0.5f };
		}

		float right() const { return position.x + size.x; }
		float left() const { return position.x; }
		float bottom() const { return position.y + size.y; }
		float top() const { return position.y; }
	};
}
