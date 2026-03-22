#include "AsciiEngine/utils/display.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/components/ascii_animation.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/utils/text.hpp"
#include <string>
#include <vector>
#include <ncurses.h>

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
		const Sprite &sprA = *a->getSprite();
		const Sprite &sprB = *b->getSprite();

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

	void mvprintwEachChar(int col, int row, const std::string &str)
	{
		for (unsigned int i = 0; i < str.size(); ++i) {
			const char &c = str[i];

			if (c != ' ')
				mvprintw(row, col + i, "%c", c);
		}
	}

	void mvprintwSprite(int col, int row, const Sprite &spr)
	{
		for (int r = 0; r < spr.height(); ++r) {
			const std::string &px = spr.pixels[r];

			/* if each char is printable, print as chars */
			if (isPrintable(px)) {
				mvprintwEachChar(col, row + r, px);
				continue;
			}

			auto spaces = getSpacePositions(px);
			int itCol = 0;

			/* print string as chunks, ignore spaces but keep
			 * print positioning */
			for (unsigned int i = 0; i < px.size();) {
				if (px[i] == ' ') {
					while (i < px.size() && px[i] == ' ') {
						++i;
						++itCol;
					}
				} else {
					unsigned int start = i;

					while (i < px.size() && px[i] != ' ')
						++i;

					std::string chunk = px.substr(start, i - start);

					mvprintw(row + r, col + itCol, "%s", chunk.c_str());
					itCol += (i - start);
				}
			}
		}
	}
}
