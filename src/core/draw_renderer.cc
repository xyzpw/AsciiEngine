#include "AsciiEngine/core/draw_renderer.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/math/ray.hpp"
#include "AsciiEngine/utils/colors.hpp"
#include "AsciiEngine/utils/display.hpp"
#include <ncurses.h>

using namespace AsciiEngine::Math;

namespace AsciiEngine
{
	void DrawRenderer::line(const Ray &ray, float distance, Color color)
	{
		const auto &[point, direction] = ray;

		int colorId = -1;
		if (color != Color::None) {
			colorId = Utils::getOrCreateColorPairId(color);
			attron(COLOR_PAIR(colorId));
		}

		for (int i = 0; i < distance; ++i) {
			Vector2 p = point + direction * i;
			mvaddch(p.y, p.x, '.');
		}

		if (color != Color::None)
			attroff(COLOR_PAIR(colorId));
	}

	void DrawRenderer::line(const Vector2 &a, const Vector2 &b,
				Color color)
	{
		auto diff = b - a;
		Ray ray(a, diff.normalized());

		line(ray, diff.magnitude(), color);
	}

	void DrawRenderer::circle(const Vector2 &point, float radius,
				  float aspectY, Color color)
	{
		int x = radius;
		int y = 0;
		int err = 0;

		const auto &[posX, posY] = point;

		int colorId = -1;
		if (color != Color::None)
			colorId = Utils::getOrCreateColorPairId(color);

		auto drawFn = [&](int dc, int dr) {
			dr *= aspectY;
			mvaddch(posY + dr, posX + dc, '.');

			if (colorId != 0)
				mvchgat(posY + dr, posX + dc, 1, A_NORMAL,
					colorId, nullptr);
		};

		while (x > y) {
			drawFn(x, y);
			drawFn(x, -y);
			drawFn(-x, y);
			drawFn(-x, -y);

			drawFn(y, x);
			drawFn(y, -x);
			drawFn(-y, x);
			drawFn(-y, -x);

			++y;

			if (err <= 0)
				err += 2*y + 1;

			if (err > 0) {
				--x;
				err -= 2*x + 1;
			}
		}
	}

	void DrawRenderer::square(const Vector2 &point, float width,
				  float height, Color color)
	{
		int colorId = -1;
		if (color != Color::None)
			colorId = Utils::getOrCreateColorPairId(color);

		int left = point.x - width * 0.5f;
		int right = point.x + width * 0.5f;
		int top = point.y - height * 0.5f;
		int bottom = point.y + height * 0.5f;

		if (colorId != -1)
			attron(COLOR_PAIR(colorId));

		for (int i = 0; i < width; ++i) {
			mvaddch(top + i, left, '|');
			mvaddch(top + i, right, '|');
		}

		std::string dash(width, '-');
		Utils::mvprintwEachChar(left, top, dash);
		Utils::mvprintwEachChar(left, bottom, dash);

		if (colorId != -1)
			attroff(COLOR_PAIR(colorId));
	}
}
