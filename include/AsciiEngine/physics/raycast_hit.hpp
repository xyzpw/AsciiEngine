#pragma once

namespace AsciiEngine
{
	struct AsciiObject;
}

namespace AsciiEngine::Physics
{
	struct RaycastHit {
		int layer;
		float distance;
		AsciiObject *object;
	};
}
