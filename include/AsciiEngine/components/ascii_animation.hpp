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

		/*
		 * return: true if active playtime is within duration
		 */
		bool isWithinDuration() { return activePlaytime <= duration; }
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
		void play(bool loop);
		void stop();
		// stop and reset animation
		void reset();
		// play the animation from the beginning
		void restart();
		bool isPlaying() { return playing; }

		/*
		 * return: true if animation is reversed
		 */
		bool isReversed() const { return reversed; }

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
		 * @duration: duration of frame in seconds
		 */
		void addFrame(Sprite frame, float duration);

		Sprite* getSprite();

		// return: number of frames in total
		int getFrameCount() { return frames.size(); }

		/*
		 * return: sum of each frame's duration
		 */
		float computeDuration() const;

		/*
		 * reverse frames play order
		 */
		void reverse();

		/*
		 * set animation to be reversed or not
		 * @value: true to reverse animation
		 */
		void setReversed(bool value);

	private:
		bool playing = false;
		bool reversed = false;
		int frameIndex = 0;
	};
}
