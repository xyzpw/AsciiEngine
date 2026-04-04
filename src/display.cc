#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/components/ascii_animation.hpp"
#include "AsciiEngine/components/hud.hpp"
#include "AsciiEngine/scene.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/utils/display.hpp"
#include "AsciiEngine/core/notification.hpp"
#include <algorithm>
#include <ncurses.h>

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

	void Engine::showToast(const std::string &text, float ttl)
	{
		notifications.emplace_back(text, ttl);
	}

	void Engine::clearToast()
	{
		notifications.clear();
	}

	void Engine::handleNotifications()
	{
		if (notifications.empty())
			return;

		/* remove expired*/
		auto tmp = std::remove_if(
				notifications.begin(),
				notifications.end(),
				[](Notification &no) {
					return no.isExpired();
				});
		notifications.erase(tmp, notifications.end());

		int r = maxRows - notifications.size();
		for (auto &no : notifications) {
			int c = maxColumns - no.text.size() - 1;
			mvprintw(r, c, "%s", no.text.c_str());

			++r;
			no.ttl -= deltaTime;
		}
	}

	void Engine::renderScene()
	{
		if (activeScene == nullptr)
			return;

		activeScene->render();
	}

	void Engine::renderHud()
	{
		auto cond = [&](AsciiObject *a) {
			return a->hasEnabledComponent<Hud>();
		};

		callOnAllActiveObjects([&](AsciiObject *ao) {
			auto *hud = ao->getComponent<Hud>();
			hud->render();
		}, cond);
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
