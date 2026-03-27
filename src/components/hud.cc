#include "AsciiEngine/components/hud.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/engine.hpp"
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
		mvprintw(position.y, position.x, "%s", text.c_str());
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
}
