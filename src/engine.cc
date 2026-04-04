#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/core/key_action.hpp"
#include "AsciiEngine/core/timer.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/scene.hpp"
#include "AsciiEngine/core/component.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/components/behaviour.hpp"
#include "AsciiEngine/components/conditional_action.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/utils/display.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include <ncurses.h>
#include <locale.h>
#include <memory>
#include <functional>
#include <vector>
#include <string>

using namespace AsciiEngine::Math;

namespace AsciiEngine
{
	std::vector<KeyAction> registeredKeys;

	int keyDown = -1;
	int delayedKeyDown = -1;
	int previousKeyDown = -1;
	float keyDownTime = 0.0f;

	Timer keyTimer;

	Engine& Engine::instance()
	{
		static Engine instance;
		return instance;
	}

	void Engine::run()
	{
		if (running)
			return;

		running = true;

		initAudio();

		setlocale(LC_ALL, "");

		/* initialize ncurses */
		initscr();
		keypad(stdscr, TRUE);
		noecho();
		nodelay(stdscr, TRUE);
		curs_set(0);
		mouseinterval(0);
		mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
		use_default_colors();
		start_color();

		// update current terminal size variables
		getmaxyx(stdscr, maxRows, maxColumns);
		midpoint = Vector2(getMidpointCol(), getMidpointRow());

		/* run user-created startup calls */
		for (auto &fn : onStartFns) {
			if (fn)
				fn();
		}

		// used to stable frame delay time
		Timer frameTimer(true);
		int keyRepeatRateMs = (KEYBOARD_REPEAT_RATE_MS * 2 + TICK_INTERVAL_MS);

		uptimeTimer.start();

		while (running) {
			++currentFrame;
			currentlyInFrame = true;

			frameTimer.restart();

			clear();

			/* get input */
			keyDown = getch();
			MouseEvent mouseEvent = getMouseEvent();

			/* update mouse state */
			if (mouseState.isDown())
				mouseState.holdTime += deltaTime;
			updateMouseState(mouseEvent);

			/* update current used key status */
			if (keyDown != -1) {
				keyTimer.stop();

				notifyBehavioursInput(keyDown);

				delayedKeyDown = keyDown;
				bool prevKeyIsCurrent = previousKeyDown == keyDown;
				float dt = 0.001f * keyTimer.completionTimeMs;

				if (keyTimer.completionTimeMs > keyRepeatRateMs) {
					previousKeyDown = -1;
					keyDownTime = 0.0f;
				} else if (prevKeyIsCurrent) {
					keyDownTime += dt;
				} else {
					keyDownTime = 0.0f;
				}

				keyTimer.restart();
			} else if (keyTimer.elapsedMs() > keyRepeatRateMs) {
				previousKeyDown = delayedKeyDown;
				delayedKeyDown = -1;

				if (keyDownTime != 0.0f)
					keyDownTime = 0.0f;
			}

			currentlyInFrame = true;

			/* detect input on registered keys */
			for (auto& it : registeredKeys) {
				if (isKeyPressed(it.key)) {
					it.action();
				}
			}

			processAllControllers();
			handleMouseInputComponents(mouseEvent);
			handleAnimations();
			checkPhysicsBodies();
			checkSpriteColliders();
			processAllConditionalActions();

			callOnBehaviours(&Behaviour::tryStart);
			updateAllBehaviours();

			renderScene();
			renderHud();
			drawObjectSprites();

			handleNotifications();

			refresh();

			int sleepTimeMs = TICK_INTERVAL_MS - frameTimer.elapsedMs();

			if (sleepTimeMs > 0)
				napms(sleepTimeMs);

			lateUpdateAllBehaviours();

			previousKeyDown = delayedKeyDown;

			frameTimer.stop();
			deltaTime = frameTimer.elapsed().count();

			currentlyInFrame = false;
		}

		cleanAudio();
		endwin();

		/* run user-created quit calls */
		for (auto &fn : onQuitFns) {
			if (fn)
				fn();
		}

		debug.printLogs();
	}

	void Engine::quit()
	{
		running = false;
	}

	void Engine::loadScene(const std::string &name)
	{
		for (size_t i = 0; i < scenes.size(); ++i) {
			auto &sc = scenes[i];

			if (!sc)
				continue;

			if (sc->name == name)
				activeScene = sc.get();
		}
	}

	void Engine::unloadScene()
	{
		activeScene = nullptr;
	}

	AsciiObject* Engine::createAsciiObject()
	{
		auto obj = std::make_unique<AsciiObject>();

		obj->id = objectCounter++;

		asciiObjects.push_back(std::move(obj));

		return asciiObjects.back().get();
	}

	AsciiObject* Engine::createAsciiObject(const std::string &name)
	{
		auto obj = std::make_unique<AsciiObject>();

		obj->id = objectCounter++;
		obj->name = name;

		asciiObjects.push_back(std::move(obj));
		return asciiObjects.back().get();
	}

	AsciiObject *Engine::createAsciiObject(const Vector2 &point,
					       const Sprite &sprite)
	{
		auto ao = std::make_unique<AsciiObject>();

		ao->id = objectCounter++;
		ao->name = "";
		ao->addComponent<AsciiRenderer>(point, sprite);

		asciiObjects.push_back(std::move(ao));
		return asciiObjects.back().get();
	}

	Scene* Engine::createScene(const std::string &name, bool load)
	{
		auto sc = std::make_unique<Scene>();
		sc->name = name;

		scenes.push_back(std::move(sc));
		if (load)
			activeScene = scenes.back().get();
		return scenes.back().get();
	}

	bool Engine::isKeyPressed(int k)
	{
		return keyDown == k;
	}

	bool Engine::isKeyJustPressed(int k)
	{
		return previousKeyDown != k && keyDown == k;
	}

	bool Engine::isKeyHeld(int k)
	{
		return previousKeyDown == k && delayedKeyDown == k;
	}

	bool Engine::isKeyReleased(int k)
	{
		if (previousKeyDown == -1)
			return false;

		return previousKeyDown == k && delayedKeyDown != k;
	}

	int Engine::currentActiveKey()
	{
		return delayedKeyDown;
	}

	float Engine::currentKeyDownTime()
	{
		return keyDownTime;
	}

	bool Engine::isSceneActive(const std::string &name)
	{
		if (activeScene != nullptr && activeScene->name == name)
			return true;
		return false;
	}

	void Engine::registerKeyAction(int key, std::function<void()> action)
	{
		registeredKeys.emplace_back(key, action);
	}

	AsciiObject* Engine::getAsciiObjectAt(int col, int row)
	{
		for (auto &ao : asciiObjects) {
			if (!ao->isActiveAndEnabled())
				continue;

			auto rend = ao->getComponent<AsciiRenderer>();
			if (rend == nullptr)
				continue;

			if (Utils::isPointInSprite(rend, col, row))
				return ao.get();
		}

		return nullptr;
	}

	AsciiObject* Engine::getAsciiObjectAt(const Math::Vector2 &v)
	{
		auto floor = v.floored();
		return getAsciiObjectAt(floor.x, floor.y);
	}

	std::vector<AsciiObject*> Engine::getAllAsciiObjects()
	{
		int size = asciiObjects.size();
		std::vector<AsciiObject*> result(size);

		for (int i = 0; i < size; ++i) {
			result[i] = asciiObjects[i].get();
		}

		return result;
	}

	std::vector<AsciiObject*> Engine::getAllAsciiObjectsByName(const std::string &name)
	{
		std::vector<AsciiObject*> result;

		for (unsigned int i = 0; i < asciiObjects.size(); ++i) {
			AsciiObject *ao = asciiObjects[i].get();

			if (ao->name == name)
				result.push_back(ao);
		}

		return result;
	}

	AsciiObject* Engine::getAsciiObjectByName(const std::string &name)
	{
		for (auto &ao : asciiObjects) {
			if (ao->name == name)
				return ao.get();
		}

		return nullptr;
	}

	AsciiObject* Engine::getAsciiObjectById(int id)
	{
		for (auto &ao : asciiObjects) {
			if (ao->id == id)
				return ao.get();
		}

		return nullptr;
	}

	void Engine::processAllConditionalActions()
	{
		for (auto &ao : asciiObjects) {
			if (!ao->isActiveAndEnabled())
				continue;

			auto comps = ao->getAllComponentsOfType<ConditionalAction>();
			for (auto *cmp : comps) {
				cmp->tryExecute();
			}
		}
	}

	void Engine::sortObjectsByLayer()
	{
		std::sort(asciiObjects.begin(), asciiObjects.end(),
			  [](auto &a, auto &b) {
				return a->layer < b->layer;
			  });
	}

	void Engine::updateAllBehaviours()
	{
		callOnBehaviours(&Behaviour::update);
	}

	void Engine::lateUpdateAllBehaviours()
	{
		callOnBehaviours(&Behaviour::lateUpdate);
	}

	void Engine::notifyBehavioursInput(int key)
	{
		callOnAllActiveObjects([&](AsciiObject *ao) {
			auto all = ao->getAllComponentsOfType<Behaviour>();
			for (auto &cmp : all) {
				if (cmp->isEnabled())
					cmp->onInput(key);
			}
		});
	}

	void Engine::callOnBehaviours(void (Behaviour::*method)())
	{
		for (auto &ao : asciiObjects) {
			if (!ao->isActiveAndEnabled())
				continue;

			auto comps = ao->getAllComponentsOfType<Behaviour>();
			for (auto *cmp : comps) {
				(cmp->*method)();
			}
		}
	}

	void Engine::callOnAllActiveObjects(std::function<void(AsciiObject*)> call)
	{
		if (!call)
			return;

		for (auto &ao : asciiObjects) {
			if (!ao->isActiveAndEnabled())
				continue;

			call(ao.get());
		}
	}

	void Engine::callOnAllActiveObjects(std::function<void(AsciiObject*)> call,
					std::function<bool(AsciiObject*)> cond)
	{
		if (!call || !cond)
			return;

		for (auto &ao : asciiObjects) {
			if (!ao->isActiveAndEnabled())
				continue;

			if (cond(ao.get()))
				call(ao.get());
		}
	}
}
