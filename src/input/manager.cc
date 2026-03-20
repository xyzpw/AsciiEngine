#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/components/controller.hpp"
#include "AsciiEngine/ascii_object.hpp"

namespace AsciiEngine
{
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
}
