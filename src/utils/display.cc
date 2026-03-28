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
		const int &rendCol = rend->position.x;
		const int &rendRow = rend->position.y;

		if (row < rendRow || row - rendRow >= spr.height())
			return false;
		else if (col < rendCol || col >= rendCol + spr.width())
			return false;

		const std::string &pixels = spr.pixels[row - rendRow];

		int pxSize = pixels.size();
		for (int i = 0; i < pxSize; ++i) {
			const char &c = pixels[i];

			if (col == rendCol + i && c != ' ')
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

		const int &aCol = a->position.x;
		const int &aRow = a->position.y;
		const int &bCol = b->position.x;
		const int &bRow = b->position.y;

		int left = std::max(aCol, bCol);
		int right = std::min(aCol + sprA.width(),  bCol + sprB.width());
		int top = std::max(aRow, bRow);
		int bottom = std::min(aRow + sprA.height(), bRow + sprB.height());

		if (left >= right || top >= bottom)
			return false;

		for (int y = top; y < bottom; ++y) {
			const std::string &rowA = sprA.pixels[y - aRow];
			const std::string &rowB = sprB.pixels[y - bRow];

			for (int x = left; x < right; ++x) {
				unsigned int ax = x - aCol;
				unsigned int bx = x - bCol;

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
