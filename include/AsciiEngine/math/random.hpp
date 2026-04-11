#pragma once

#include "AsciiEngine/math/vector2.hpp"

namespace AsciiEngine::Math
{
	/*
	 * return: random number from 0 to 1
	 */
	float randomNumber();
	float randomNumber(float minInclusive, float maxInclusive);

	/*
	 * return: vector2 with randomized values
	 */
	Vector2 randomVector2();
	Vector2 randomVector2(float minInclusive, float maxInclusive);

	/*
	 * return: random vector2 from 0 to max
	 */
	Vector2 randomVector2(const Vector2 &maxInclusive);
}
