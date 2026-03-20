#include "AsciiEngine/math/vector2.hpp"
#include <cmath>

namespace AsciiEngine::Math
{
	const Vector2 Vector2::right = Vector2(1, 0);
	const Vector2 Vector2::left = Vector2(-1, 0);
	const Vector2 Vector2::down = Vector2(0, 1);
	const Vector2 Vector2::up = Vector2(0, -1);

	float Vector2::magnitude() const
	{
		return std::sqrt(x*x + y*y);
	}

	float Vector2::sqrMagnitude() const
	{
		return x*x + y*y;
	}

	Vector2 Vector2::normalized() const
	{
		float mag = magnitude();

		if (mag == 0.0f)
			return Vector2(0.0f, 0.0f);

		return Vector2(x / mag, y / mag);
	}

	Vector2 Vector2::rounded() const
	{
		return Vector2(std::round(x), std::round(y));
	}

	Vector2 Vector2::floored() const
	{
		return Vector2(std::floor(x), std::floor(y));
	}

	std::ostream& operator<<(std::ostream &os, const Vector2 &v2) {
		os << "(" << v2.x << ", " << v2.y << ")";
		return os;
	}
}
