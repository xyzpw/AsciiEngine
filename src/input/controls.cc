#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include <ncurses.h>

namespace AsciiEngine
{
	Controller* AsciiObject::addController(MovementControlType t)
	{
		auto rend = getComponent<AsciiRenderer>();

		if (rend == nullptr)
			return nullptr;

		auto controller = addComponent<Controller>();
		std::unordered_map<int, std::function<void()>> keyMap;

		auto addMovements = [this, &keyMap, rend](int r, int l, int d, int u)
		{
			keyMap[r] = [rend]() { rend->moveX(1); };
			keyMap[l] = [rend]() { rend->moveX(-1); };
			keyMap[d] = [rend]() { rend->moveY(1); };
			keyMap[u] = [rend]() { rend->moveY(-1); };
		};

		switch (t) {
		case MovementControlType::WASD:
				addMovements('d', 'a', 's', 'w');
				break;
		case MovementControlType::ArrowKeys:
				addMovements(KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP);
				break;
		case MovementControlType::Vim:
				addMovements('l', 'h', 'j', 'k');
				break;
		default:
				break;
		}

		controller->keyFunctionMap = keyMap;

		return controller;
	}
}
