#pragma once

#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/math/ray.hpp"
#include "AsciiEngine/common/color.hpp"

namespace AsciiEngine
{
	struct DrawRenderer {
		/*
		 * draw line on screen this frame
		 */
		void line(const Math::Ray &ray, float distance,
			  Color color = Color::None);

		/*
		 * draw a line between two points
		 * @a: original point of line
		 * @b: the end point of the line
		 */
		void line(const Math::Vector2 &a, const Math::Vector2 &b,
			  Color color = Color::None);

		/*
		 * draw a circle on the screen this frame
		 * @point: point at center of circle
		 * @aspectY: radius multiplier on Y-axis for aspect correction
		 */
		void circle(const Math::Vector2 &point, float radius,
			    float aspectY = 0.5f, Color color = Color::None);

		/*
		 * draw square on screen this frame
		 * @point: center of square
		 */
		void square(const Math::Vector2 &point, float width,
			    float height, Color color = Color::None);
	};
}
