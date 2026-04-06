#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/common/color.hpp"
#include "AsciiEngine/utils/colors.hpp"
#include "AsciiEngine/utils/display.hpp"
#include "AsciiEngine/engine.hpp"

namespace AsciiEngine
{
	void AsciiRenderer::render()
	{
		setAttrStatus(true);

		Utils::mvprintwSprite(position.x, position.y, *getSprite());

		setAttrStatus(false);
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

	Sprite* AsciiRenderer::getSprite()
	{
		if (animationSprite == nullptr)
			return &sprite;
		return animationSprite;
	}

	const Sprite* AsciiRenderer::getSprite() const
	{
		if (animationSprite == nullptr)
			return &sprite;
		return animationSprite;
	}

	void AsciiRenderer::setAttrStatus(bool value)
	{
		bool hasCol = colorPairId.has_value();
		int colId = hasCol ? colorPairId.value() : -1;

		if (hasCol && value)
			attron(COLOR_PAIR(colId));
		else if (hasCol && !value)
			attroff(COLOR_PAIR(colId));

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
