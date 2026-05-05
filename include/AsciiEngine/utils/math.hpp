#pragma once

#include "AsciiEngine/math/bounds.hpp"

namespace AsciiEngine::Utils
{
	bool boundsOverlap(const Math::Bounds &a, const Math::Bounds &b);

	template<typename T, typename U>
	constexpr T lerp(T a, T b, U t) noexcept
	{
		return a + t * (b - a);
	}

	template<typename T, typename U>
	constexpr T inverseLerp(T a, T b, U value) noexcept
	{
		return (value - a) / (b - a);
	}

	/*
	 * return: value clamped between 0 and 1
	 */
	template<typename T>
	constexpr T clamp01(T value) noexcept
	{
		if (value < 0)
			return 0;
		if (value > 1)
			return 1;

		return value;
	}
}
