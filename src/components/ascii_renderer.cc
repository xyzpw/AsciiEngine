#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/common/color.hpp"
#include "AsciiEngine/utils/colors.hpp"
#include "AsciiEngine/engine.hpp"
#include <ncurses.h>
#include <string>

namespace AsciiEngine
{
	void AsciiRenderer::render()
	{
		bool hasCol = colorPairId.has_value();

		if (hasCol) {
			attron(COLOR_PAIR(colorPairId.value()));
		}

		int lines = sprite.height();
		for (int i = 0; i < lines; ++i) {
			const std::string &px = sprite.pixels[i];
			int pxSize = px.size();

			for (int j = 0; j < pxSize; ++j) {
				const char &c = px[j];

				if (c != ' ')
					mvprintw(row + i, col + j, "%c", c);
			}
		}

		if (hasCol) {
			attroff(COLOR_PAIR(colorPairId.value()));
		}
	}

	void AsciiRenderer::setColor(Color fg, Color bg)
	{
		int id = Utils::getOrCreateColorPairId(fg, bg);
		colorPairId = id;
	}

	Color AsciiRenderer::getFgColor()
	{
		if (!colorPairId.has_value())
			return Color::None;

		return colorRegistry[colorPairId.value()].fg;
	}

	Color AsciiRenderer::getBgColor()
	{
		if (!colorPairId.has_value())
			return Color::None;

		return colorRegistry[colorPairId.value()].bg;
	}
}
