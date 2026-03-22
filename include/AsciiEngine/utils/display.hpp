#pragma once

#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/common/sprite.hpp"

namespace AsciiEngine
{
	struct AsciiObject;
}

namespace AsciiEngine::Utils
{
	/* check if a sprite contains a pixel appearing at the specified point */
	/*
	 * return: true if the renderer's sprite contains a char at the
	 * coordinates (excludes spaces)
	 */
	bool isPointInSprite(const AsciiRenderer *rend, int col, int row);
	bool isPointInSprite(const AsciiRenderer *rend, const Math::Vector2 &v);

	/*
	 * return: true if the two sprites contain an overlapping char
	 * (excluding spaces)
	 */
	bool spritesOverlap(const AsciiRenderer *a, const AsciiRenderer *b);

	/*
	 * return: true if the object has a renderer and it is visible
	 */
	bool hasVisibleRenderer(AsciiObject *a);

	/*
	 * Prints each char one-by-one instead of a whole string,
	 * ignores spaces but keeps the positioning correct.
	 */
	void mvprintwEachChar(int col, int row, const std::string &str);

	/*
	 * prints the sprite
	 */
	void mvprintwSprite(int col, int row, const Sprite &spr);
}
