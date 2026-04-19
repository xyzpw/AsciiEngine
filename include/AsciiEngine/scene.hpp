#pragma once

#include <vector>
#include <memory>
#include <string>
#include <functional>
#include "AsciiEngine/components/ascii_renderer.hpp"

namespace AsciiEngine
{
	struct Scene {
		std::string name;

		std::vector<std::unique_ptr<AsciiRenderer>> renderers;

		void render();
		AsciiRenderer* createRenderer(int col, int row, const std::vector<std::string> &spr);
		AsciiRenderer* getRendererAt(int col, int row);

		/*
		 * call function after scene is loaded
		 */
		void setOnLoad(std::function<void()> call)
		{
			onLoad = call;
		}

		/*
		 * call function after unloading scene
		 */
		void setOnUnload(std::function<void()> call)
		{
			onUnload = call;
		}

		void callOnLoad()
		{
			if (onLoad)
				onLoad();
		}

		void callOnUnload()
		{
			if (onUnload)
				onUnload();
		}

	private:
		std::function<void()> onLoad;
		std::function<void()> onUnload;
	};
}
