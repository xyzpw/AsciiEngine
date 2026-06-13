#include "AsciiEngine/components/hud.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/utils/colors.hpp"
#include <string>
#include <ncurses.h>

using namespace AsciiEngine::Math;

namespace AsciiEngine
{
	Hud::Hud(const std::string &text, const Vector2 &point)
	{
		this->text = text;
		this->position = point;
	}

	void Hud::render()
	{
		setAttrStatus(true);
		mvprintw(position.y, position.x, "%s", text.c_str());
		setAttrStatus(false);
	}

	void Hud::centerTextColumn()
	{
		auto &instance = Engine::instance();

		if (!instance.isRunning())
			return;

		int mid = instance.getMidpointCol();
		int halfSize = 0.5f * text.size();

		position.x = mid - halfSize;
	}

	void Hud::setColor(Color fgColor, Color bgColor)
	{
		colorPairId = Utils::getOrCreateColorPairId(fgColor, bgColor);
	}

	Color Hud::getFgColor() const
	{
		if (colorPairId == -1)
			return Color::None;

		return colorRegistry[colorPairId].fg;
	}

	Color Hud::getBgColor() const
	{
		if (colorPairId == -1)
			return Color::None;

		return colorRegistry[colorPairId].bg;
	}

	void Hud::setAttrStatus(bool value)
	{
		if (colorPairId != -1 && value)
			attron(COLOR_PAIR(colorPairId));
		else if (colorPairId != -1 && !value)
			attroff(COLOR_PAIR(colorPairId));

		if (bold && value)
			attron(A_BOLD);
		else if (bold && !value)
			attroff(A_BOLD);

		if (blink && value)
			attron(A_BLINK);
		else if (blink && !value)
			attroff(A_BLINK);
	}
}
