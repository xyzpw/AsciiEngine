#include "AsciiEngine/components/ascii_animation.hpp"
#include "AsciiEngine/common/sprite.hpp"
#include "AsciiEngine/utils/display.hpp"
#include <algorithm>
#include <string>

namespace AsciiEngine
{
	AsciiAnimation::AsciiAnimation(
			std::string name,
			std::vector<Sprite> sprites,
			float duration)
	{
		name = name;

		float frameDur = (duration / (float)sprites.size());

		for (const auto &fr : sprites) {
			frames.emplace_back(fr, frameDur);
		}
	}

	void AsciiAnimation::addFrame(Sprite frame, float duration)
	{
		frames.emplace_back(frame, duration);
	}

	void AsciiAnimation::play()
	{
		if (!Utils::hasVisibleRenderer(owner))
			return;

		playing = true;
	}

	void AsciiAnimation::play(bool loop)
	{
		if (!Utils::hasVisibleRenderer(owner))
			return;

		playing = true;
		this->loop = loop;
	}

	void AsciiAnimation::stop()
	{
		playing = false;
	}

	void AsciiAnimation::reset()
	{
		for (auto &fr : frames) {
			fr.activePlaytime = 0;
		}

		frameIndex = 0;
	}

	void AsciiAnimation::restart()
	{
		reset();
		playing = true;
	}

	AnimationFrame* AsciiAnimation::tick(float dt)
	{
		if (frames.size() == 0 || !playing)
			return nullptr;

		auto *frame = &frames[frameIndex];
		frame->activePlaytime += dt;

		if (frame->activePlaytime <= frame->duration)
			return frame;

		frame->activePlaytime = 0;
		int maxIndex = getFrameCount() - 1;

		if (frameIndex == maxIndex && loop)
			frameIndex = 0;
		else if (!loop && frameIndex == maxIndex)
			playing = false;
		else
			frameIndex = std::clamp(frameIndex + 1, 0, maxIndex);

		return &frames[frameIndex];
	}

	Sprite* AsciiAnimation::getSprite()
	{
		frameIndex = std::clamp(frameIndex, 0, (int)frames.size() - 1);
		return &frames[frameIndex].sprite;
	}

	float AsciiAnimation::computeDuration() const
	{
		float dur = 0;

		for (const auto &fr : frames) {
			dur += fr.duration;
		}

		return dur;
	}
}
