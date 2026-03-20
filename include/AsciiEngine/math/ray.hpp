#pragma once

#include "AsciiEngine/math/vector2.hpp"

namespace AsciiEngine::Math
{
	struct Ray {
		Vector2 point;
		Vector2 direction;

		/*
		 * @point: origin point
		 * @direction: pointing direction
		 */
		Ray(const Vector2 &point, const Vector2 &direction)
			: point(point), direction(direction) {}
	};
}
