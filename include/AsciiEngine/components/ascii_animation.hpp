#pragma once

#include "AsciiEngine/core/component.hpp"
#include "AsciiEngine/common/sprite.hpp"
#include <string>

namespace AsciiEngine
{
	struct AnimationFrame {
		Sprite sprite;
		float duration;
		float activePlaytime = 0;

		AnimationFrame(Sprite sprite, float duration)
			: sprite(sprite), duration(duration) {}
	};

	struct AsciiAnimation : Component {
		std::string name = "";
		std::vector<AnimationFrame> frames;
		bool loop = false;

		AsciiAnimation(std::string name,
				std::vector<AnimationFrame> frames)
			: name(name), frames(frames) {}
		/*
		 * @name: name of animation
		 * @sprites: each sprite of the animation
		 * @duration: duration of full animation in seconds
		 */
		AsciiAnimation(std::string name, std::vector<Sprite> sprites,
				float duration);

		void play();
		void play(bool loop = false);
		void stop();
		// stop and reset animation
		void reset();
		// play the animation from the beginning
		void restart();
		bool isPlaying() { return playing; }

		/*
		 * called every frame to keep the animation playing
		 * @dt: time passed since last tick
		 *
		 * return: the current frame
		 */
		AnimationFrame* tick(float dt);

		/*
		 * add a frame to the animation
		 * @frame: sprite of frame
		 * @durationMs: duration of frame in seconds
		 */
		void addFrame(Sprite frame, float duration);

		Sprite* getSprite();

		// return: number of frames in total
		int getFrameCount() { return frames.size(); }

	private:
		bool playing = false;
		int frameIndex = 0;
	};
}
