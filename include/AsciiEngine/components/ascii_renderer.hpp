#pragma once

#include <string>
#include <ncurses.h>
#include <optional>
#include <vector>
#include "AsciiEngine/core/component.hpp"
#include "AsciiEngine/common/color.hpp"
#include "AsciiEngine/common/sprite.hpp"
#include "AsciiEngine/math/vector2.hpp"

namespace AsciiEngine
{
	struct AsciiRenderer : Component {
		Math::Vector2 position;

		Sprite sprite;
		Sprite *animationSprite = nullptr;
		std::optional<int> colorPairId;

		AsciiRenderer(int x, int y, std::vector<std::string> rows)
			: position(x, y), sprite(rows) {}

		AsciiRenderer(int x, int y, const Sprite &spr)
			: position(x, y), sprite(spr) {}

		AsciiRenderer(const Math::Vector2 &point, const Sprite &spr) :
			position(point), sprite(spr) {}

		AsciiRenderer(int x, int y, const std::string &spr)
			: position(x, y), sprite(Sprite({ spr })) {}

		AsciiRenderer(const Math::Vector2 &point, const std::string &spr) :
			position(point), sprite(Sprite( { spr })) {}

		AsciiRenderer(int x, int y) : position(x, y) {}

		void render();

		Sprite* getSprite();
		const Sprite* getSprite() const;

		void setColor(Color fg, Color bg = Color::None);
		void clearColor() { colorPairId = std::nullopt; }
		Color getFgColor();
		Color getBgColor();

		void move(int dx, int dy) { position.x += dx; position.y += dy; }
		void moveX(int dx) { move(dx, 0); }
		void moveY(int dy) { move(0, dy); }
		void moveTo(int newCol, int newRow)
			{ position.x = newCol; position.y = newRow; }

		bool isVisible() { return visible; }
		void setVisible(bool value) { visible = value; }

	protected:
		bool visible = true;
	};
}
