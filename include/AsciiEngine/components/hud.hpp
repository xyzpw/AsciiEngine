#pragma once

#include "AsciiEngine/core/component.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include <string>

namespace AsciiEngine
{
	struct Hud : Component {
		std::string text;
		Math::Vector2 position;

		Hud(const std::string &text) : text(text) {}
		Hud(const std::string &text, const Math::Vector2 &point);

		void render();

		/*
		 * center text column to center of screen
		 *
		 * Ncurses must be initialized before calling.
		 */
		void centerTextColumn();
	};
}
