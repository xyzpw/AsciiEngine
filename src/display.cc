#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/scene.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/utils/display.hpp"
#include <algorithm>

namespace AsciiEngine
{
	bool Engine::isInDisplay(int col, int row)
	{
		if (col < 0 || row < 0)
			return false;
		return col < maxColumns && row < maxRows;
	}

	bool Engine::isInDisplay(const Math::Vector2 &v)
	{
		auto floor = v.floored();
		return isInDisplay(floor.x, floor.y);
	}

	void Engine::renderScene()
	{
		if (activeScene == nullptr)
			return;

		activeScene->render();
	}

	void Engine::drawObjectSprites()
	{
		/* sort layers in ascending order */
		std::sort(asciiObjects.begin(), asciiObjects.end(),
			  [](auto &a, auto &b) {
				return a->layer < b->layer;
			  });

		/* draw to screen */
		callOnAllActiveObjects([&](AsciiObject *it) {
			auto rend = it->getComponent<AsciiRenderer>();
			rend->render();
		}, Utils::hasVisibleRenderer);
	}
}
