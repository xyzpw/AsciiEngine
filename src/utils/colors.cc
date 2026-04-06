#include "AsciiEngine/utils/colors.hpp"
#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/common/color.hpp"
#include <ncurses.h>

namespace AsciiEngine::Utils
{
	bool running = false;

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

		if (!running)
			running = Engine::instance().isRunning();

		if (running)
			init_pair(col.pairId, (int)fg, (int)bg);
		colorRegistry[col.pairId] = col;

		return col.pairId;
	}
}
