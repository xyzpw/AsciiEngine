#include "AsciiEngine/utils/math.hpp"
#include "AsciiEngine/math/bounds.hpp"

using namespace AsciiEngine::Math;

namespace AsciiEngine::Utils
{
	bool boundsOverlap(const Bounds &a, const Bounds &b)
	{
		return !(
				a.right() <= b.left() ||
				a.left() >= b.right() ||
				a.bottom() <= b.top() ||
				a.top() >= b.bottom()
			);
	}
}
