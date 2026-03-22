#pragma once

#include <string>
#include <ncurses.h>
#include <optional>
#include <vector>
#include "AsciiEngine/core/component.hpp"
#include "AsciiEngine/common/color.hpp"
#include "AsciiEngine/common/sprite.hpp"

namespace AsciiEngine
{
	struct AsciiRenderer : Component {
		int col;
		int row;

		Sprite sprite;
		Sprite *animationSprite = nullptr;
		std::optional<int> colorPairId;

		AsciiRenderer(int x, int y, std::vector<std::string> rows)
			: col(x), row(y), sprite(rows) {}
		AsciiRenderer(int x, int y, Sprite spr)
			: col(x), row(y), sprite(spr) {}
		AsciiRenderer(int x, int y, std::string spr)
			: col(x), row(y), sprite(Sprite({ spr })) {}
		AsciiRenderer(int x, int y) : col(x), row(y) {}

		void render();

		void setColor(Color fg, Color bg = Color::None);
		void clearColor() { colorPairId = std::nullopt; }
		Color getFgColor();
		Color getBgColor();

		void move(int dx, int dy) { col += dx; row += dy; }
		void moveX(int dx) { move(dx, 0); }
		void moveY(int dy) { move(0, dy); }
		void moveTo(int newCol, int newRow) { col = newCol; row = newRow; }

		bool isVisible() { return visible; }
		void setVisible(bool value) { visible = value; }

	protected:
		bool visible = true;
	};
}
