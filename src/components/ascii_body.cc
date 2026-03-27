#include "AsciiEngine/components/ascii_body.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/math/bounds.hpp"

namespace AsciiEngine
{
	AsciiBody::AsciiBody(float x, float y, float width, float height)
	{
		bounds.position.x = x;
		bounds.position.y = y;

		bounds.size.x = width;
		bounds.size.y = height;
	}
}
