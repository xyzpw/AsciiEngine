#pragma once

#include "AsciiEngine/core/component.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/common/color.hpp"
#include <string>

namespace AsciiEngine
{
	struct Hud : Component {
		std::string text;
		Math::Vector2 position;

		bool blink = false;
		bool bold = false;

		Hud(const std::string &text) : text(text) {}
		Hud(const std::string &text, const Math::Vector2 &point);

		void render();

		/*
		 * center text column to center of screen
		 *
		 * Ncurses must be initialized before calling.
		 */
		void centerTextColumn();

		/*
		 * set color of text
		 */
		void setColor(Color fg, Color bg = Color::None);

		void clearColor() { colorPairId = -1; }

		Color getFgColor() const;
		Color getBgColor() const;

		private:
		int colorPairId = -1;

		void setAttrStatus(bool value);
	};
}
