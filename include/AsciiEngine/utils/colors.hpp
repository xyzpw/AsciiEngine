#pragma once

#include "AsciiEngine/common/color.hpp"

namespace AsciiEngine::Utils
{
	int getOrCreateColorPairId(Color fg, Color bg = Color::None);
}
