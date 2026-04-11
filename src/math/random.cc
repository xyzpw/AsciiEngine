#include "AsciiEngine/math/random.hpp"
#include <random>

std::mt19937 mtEng(std::random_device{}());
std::uniform_real_distribution<float> uniformRealDist(0.0f, 1.0f);

namespace AsciiEngine::Math
{
	float randomNumber()
	{
		return uniformRealDist(mtEng);
	}

	float randomNumber(float minInclusive, float maxInclusive)
	{
		float r = randomNumber();

		return minInclusive + (maxInclusive - minInclusive) * r;
	}

	Vector2 randomVector2()
	{
		return Vector2(randomNumber(), randomNumber());
	}

	Vector2 randomVector2(float minInclusive, float maxInclusive)
	{
		float x = randomNumber(minInclusive, maxInclusive);
		float y = randomNumber(minInclusive, maxInclusive);

		return Vector2(x, y);
	}

	Vector2 randomVector2(const Vector2 &maxInclusive)
	{
		float x = randomNumber(0, maxInclusive.x);
		float y = randomNumber(0, maxInclusive.y);

		return Vector2(x, y);
	}
}
