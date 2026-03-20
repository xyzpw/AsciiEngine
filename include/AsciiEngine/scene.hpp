#pragma once

#include <vector>
#include <memory>
#include <string>
#include "AsciiEngine/components/ascii_renderer.hpp"

namespace AsciiEngine
{
	struct Scene {
		std::string name;

		std::vector<std::unique_ptr<AsciiRenderer>> renderers;

		void render();
		AsciiRenderer* createRenderer(int col, int row, const std::vector<std::string> &spr);
		AsciiRenderer* getRendererAt(int col, int row);
	};
}
