#pragma once

#include "AsciiEngine/core/component.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/math/bounds.hpp"

namespace AsciiEngine
{
	struct AsciiBody : Component {
		Math::Bounds bounds;

		float gravityModifier = 1;

		Math::Vector2 velocity;

		bool isStatic = false;

		/*
		 * @x: column position
		 * @y: row position
		 * @width: width of body
		 * @height: height of body
		 */
		AsciiBody(float x, float y, float width = 1.0f,
			  float height = 1.0f);

		void setWidth(float w) { bounds.size.x = w; };
		void setHeight(float h) { bounds.size.y = h; };

		void setStatic(bool value) { isStatic = value; }

		void setGravityModifier(float f) { gravityModifier = f; }

		Math::Vector2& getPosition() { return bounds.position; }
		Math::Vector2& getSize() { return bounds.size; }
	};
}
