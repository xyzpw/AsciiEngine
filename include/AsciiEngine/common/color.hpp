#pragma once

#include <ncurses.h>

namespace AsciiEngine
{
	enum class Color {
		None = -1,
		Black = COLOR_BLACK,
		Red = COLOR_RED,
		Green = COLOR_GREEN,
		Yellow = COLOR_YELLOW,
		Blue = COLOR_BLUE,
		Magenta = COLOR_MAGENTA,
		Cyan = COLOR_CYAN,
		White = COLOR_WHITE,
	};

	struct ColorPair {
		int pairId;
		Color fg, bg;
	};
}
