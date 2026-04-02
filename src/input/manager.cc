#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/components/controller.hpp"
#include "AsciiEngine/components/clickable.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/core/mouse_state.hpp"
#include "AsciiEngine/utils/display.hpp"
#include <ncurses.h>

namespace AsciiEngine
{
	constexpr mmask_t LEFT_MOUSE_MASK = BUTTON1_PRESSED | BUTTON1_RELEASED;
	constexpr mmask_t MIDDLE_MOUSE_MASK = BUTTON2_PRESSED | BUTTON2_RELEASED;
	constexpr mmask_t RIGHT_MOUSE_MASK = BUTTON3_PRESSED | BUTTON3_RELEASED;
	constexpr mmask_t BUTTON_PRESSED_MASK =
		BUTTON1_PRESSED | BUTTON2_PRESSED | BUTTON3_PRESSED;
	constexpr mmask_t BUTTON_RELEASED_MASK =
		BUTTON1_RELEASED | BUTTON2_RELEASED | BUTTON3_RELEASED;

	void Engine::processController(Controller* ctrl)
	{
		for (auto &it : ctrl->keyFunctionMap) {
			if (isKeyPressed(it.first) && it.second)
				it.second();
		}
	}

	void Engine::processAllControllers()
	{
		for (auto &AO : asciiObjects) {
			if (!AO->isActiveAndEnabled())
				continue;

			auto controllers = AO->getAllComponentsOfType<Controller>();
			for (auto *ctrl : controllers) {
				processController(ctrl);
			}
		}
	}

	void Engine::updateMouseState(const MouseEvent& e)
	{
		if (e)
			applyMouseEventToState(e);
	}

	MouseEvent Engine::getMouseEvent()
	{
		MouseEvent event;

		MEVENT e;
		if (getmouse(&e) != OK)
			return event;

		event.position.x = e.x;
		event.position.y = e.y;

		if (e.bstate & LEFT_MOUSE_MASK)
			event.button = MouseButton::LEFT;
		else if (e.bstate & MIDDLE_MOUSE_MASK)
			event.button = MouseButton::MIDDLE;
		else if (e.bstate & RIGHT_MOUSE_MASK)
			event.button = MouseButton::RIGHT;

		if (e.bstate & BUTTON_PRESSED_MASK)
			event.action = MouseAction::PRESS;
		else if (e.bstate & BUTTON_RELEASED_MASK)
			event.action = MouseAction::RELEASE;

		return event;
	}

	void Engine::applyMouseEventToState(const MouseEvent &e)
	{
		if (e.action == MouseAction::PRESS) {
			mouseState.button = e.button;
			mouseState.holdTime = 0;
			mouseState.position = e.position;
		} else if (e.action == MouseAction::RELEASE) {
			mouseState.reset();
			mouseState.position = e.position;
		}
	}

	void Engine::handleMouseInputComponents(const MouseEvent &e)
	{
		auto isValid = [&](AsciiObject *a) {
			return a->hasEnabledComponent<Clickable>() &&
				Utils::hasVisibleRenderer(a);
		};

		callOnAllActiveObjects([&](AsciiObject *ao) {
			auto click = ao->getComponent<Clickable>();
			auto rend = ao->getComponent<AsciiRenderer>();

			if (!Utils::isPointInSprite(rend, e.position))
				return;

			if (e.action == MouseAction::PRESS)
				click->onMouseDown(mouseState);
			else if (e.action == MouseAction::RELEASE)
				click->onMouseUp(mouseState);
			else if (mouseState.isDown())
				click->onHold(mouseState);
		}, isValid);
	}
}
