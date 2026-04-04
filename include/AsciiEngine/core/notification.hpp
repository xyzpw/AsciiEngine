#pragma once

#include <string>

namespace AsciiEngine
{
	struct Notification {
		std::string text;
		float ttl;

		Notification(const std::string &text, float ttl) :
			text(text), ttl(ttl) {}

		bool isExpired() { return ttl < 0; }
	};
}
