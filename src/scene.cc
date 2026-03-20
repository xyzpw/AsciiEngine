#include "AsciiEngine/scene.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/utils/display.hpp"
#include <ncurses.h>
#include <string>
#include <memory>
#include <vector>

namespace AsciiEngine
{
	void Scene::render()
	{
		for (auto &rend : renderers) {
			if (rend->isVisible())
				rend->render();
		}
	}

	AsciiRenderer* Scene::createRenderer(int col, int row, const std::vector<std::string> &spr)
	{
		std::unique_ptr<AsciiRenderer> rend = std::make_unique<AsciiRenderer>(col, row, spr);

		renderers.push_back(std::move(rend));
		return renderers.back().get();
	}

	AsciiRenderer* Scene::getRendererAt(int col, int row)
	{
		for (auto &rend : renderers) {
			if (!rend->isVisible())
				continue;

			if (Utils::isPointInSprite(rend.get(), col, row))
				return rend.get();
		}

		return nullptr;
	}
}
