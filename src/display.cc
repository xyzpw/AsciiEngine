#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/components/ascii_animation.hpp"
#include "AsciiEngine/scene.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/utils/display.hpp"

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
		sortObjectsByLayer();

		/* draw to screen */
		callOnAllActiveObjects([&](AsciiObject *it) {
			auto rend = it->getComponent<AsciiRenderer>();
			rend->render();
		}, Utils::hasVisibleRenderer);
	}

	void Engine::handleAnimations()
	{
		auto isValid = [&](AsciiObject *a) {
			if (!Utils::hasVisibleRenderer(a))
				return false;
			auto *an = a->getComponent<AsciiAnimation>();
			return an != nullptr && an->isEnabled();
		};

		callOnAllActiveObjects([&](AsciiObject *ao) {
			auto *rend = ao->getComponent<AsciiRenderer>();
			auto animLs = ao->getAllComponentsOfType<AsciiAnimation>();

			rend->animationSprite = nullptr;

			for (auto *anim : animLs) {
				if (!anim->isPlaying())
					continue;

				anim->tick(deltaTime);
				rend->animationSprite = anim->getSprite();
			}
		}, isValid);
	}
}
