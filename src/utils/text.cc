#include "AsciiEngine/utils/text.hpp"
#include <string>
#include <vector>
#include <cctype>
#include <cstdarg>
#include <cstdio>

namespace AsciiEngine::Utils
{
	std::vector<int> getSpacePositions(const std::string &str)
	{
		std::vector<int> result;

		for (unsigned int i = 0; i < str.size(); ++i) {
			const char &c = str[i];

			if (c == ' ')
				result.push_back(i);
		}

		return result;
	}

	bool isPrintable(const std::string &str)
	{
		for (const char &c : str) {
			if (!std::isprint(c))
				return false;
		}

		return true;
	}

	std::string formatText(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);

		char buf[1024];
		vsnprintf(buf, sizeof(buf), fmt, args);

		va_end(args);

		return buf;
	}
}
