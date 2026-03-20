#pragma once

#include <string>
#include <vector>

namespace AsciiEngine
{
	struct Sprite {
		std::vector<std::string> pixels;

		Sprite(const std::vector<std::string> &rows) : pixels(rows) {}
		Sprite() {}

		int width() const
		{
			int max = 0;
			for (const auto &it : pixels) {
				int size = it.size();
				if (size > max)
					max = size;
			}

			return max;
		}

		int height() const { return pixels.size(); }
	};
}
