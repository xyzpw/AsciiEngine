#pragma once

#include <string>
#include <vector>

namespace AsciiEngine::Utils
{
	std::vector<int> getSpacePositions(const std::string &str);
	bool isPrintable(const std::string &str);
}
