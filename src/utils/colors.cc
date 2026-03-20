#include "AsciiEngine/utils/colors.hpp"
#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/common/color.hpp"
#include <ncurses.h>

namespace AsciiEngine::Utils
{
	int getOrCreateColorPairId(Color fg, Color bg)
	{
		int maxId = 0;

		for (const auto &[id, c] : colorRegistry) {
			if (id > maxId)
				maxId = id;

			if (c.fg == fg && c.bg == bg)
				return id;
		}

		ColorPair col;
		col.pairId = maxId + 1;
		col.fg = fg;
		col.bg = bg;

		init_pair(col.pairId, static_cast<int>(fg), static_cast<int>(bg));
		colorRegistry[col.pairId] = col;

		return col.pairId;
	}
}
