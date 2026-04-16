#pragma once

#include "AsciiEngine/math/vector2.hpp"

namespace AsciiEngine
{
	struct AsciiObject;
}

namespace AsciiEngine::Physics
{
	struct RaycastHit {
		int layer;
		float distance;
		Math::Vector2 point;
		AsciiObject *object;
	};
}
