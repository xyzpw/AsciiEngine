#include "AsciiEngine/utils/display.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include <string>

using namespace AsciiEngine::Math;

namespace AsciiEngine::Utils
{
	bool isPointInSprite(const AsciiRenderer *rend, int col, int row)
	{
		const Sprite &spr = rend->sprite;

		if (row < rend->row || row - rend->row >= spr.height())
			return false;
		else if (col < rend->col || col >= rend->col + spr.width())
			return false;

		const std::string &pixels = spr.pixels[row - rend->row];

		int pxSize = pixels.size();
		for (int i = 0; i < pxSize; ++i) {
			const char &c = pixels[i];

			if (col == rend->col + i && c != ' ')
				return true;
		}

		return false;
	}

	bool isPointInSprite(const AsciiRenderer *rend, const Vector2 &v)
	{
		auto floor = v.floored();
		return isPointInSprite(rend, floor.x, floor.y);
	}

	bool spritesOverlap(const AsciiRenderer *a, const AsciiRenderer *b)
	{
		const Sprite &sprA = a->sprite;
		const Sprite &sprB = b->sprite;

		int left = std::max(a->col, b->col);
		int right = std::min(a->col + sprA.width(),  b->col + sprB.width());
		int top = std::max(a->row, b->row);
		int bottom = std::min(a->row + sprA.height(), b->row + sprB.height());

		if (left >= right || top >= bottom)
			return false;

		for (int y = top; y < bottom; ++y) {
			const std::string &rowA = sprA.pixels[y - a->row];
			const std::string &rowB = sprB.pixels[y - b->row];

			for (int x = left; x < right; ++x) {
				unsigned int ax = x - a->col;
				unsigned int bx = x - b->col;

				char ca = (ax < rowA.size()) ? rowA[ax] : ' ';
				char cb = (bx < rowB.size()) ? rowB[bx] : ' ';

				if (ca != ' ' && cb != ' ')
					return true;
			}
		}

		return false;
	}

	bool hasVisibleRenderer(AsciiObject *a)
	{
		auto rend = a->getComponent<AsciiRenderer>();
		return rend != nullptr && rend->isVisible();
	}
}
