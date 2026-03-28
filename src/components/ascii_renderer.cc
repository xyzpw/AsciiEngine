#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/common/color.hpp"
#include "AsciiEngine/utils/colors.hpp"
#include "AsciiEngine/utils/display.hpp"
#include "AsciiEngine/engine.hpp"

namespace AsciiEngine
{
	void AsciiRenderer::render()
	{
		bool hasCol = colorPairId.has_value();

		if (hasCol) {
			attron(COLOR_PAIR(colorPairId.value()));
		}

		Utils::mvprintwSprite(position.x, position.y, *getSprite());

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
}
