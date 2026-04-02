#include "AsciiEngine/components/audio_source.hpp"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <string>

namespace AsciiEngine
{
	AudioSource::AudioSource(const std::string &file)
	{
		if (file.empty())
			return;

		filename = file;

		loadAudioFile();
	}

	AudioSource::AudioSource(const std::string &name,
				 const std::string &file)
	{
		if (file.empty())
			return;

		this->name = name;
		filename = file;

		loadAudioFile();
	}

	Mix_Chunk *AudioSource::getAudioChunk()
	{
		if (!hasSound)
			return nullptr;

		return audioChunk;
	}

	void AudioSource::freeChunk()
	{
		Mix_FreeChunk(audioChunk);
		hasSound = false;
	}

	void AudioSource::loadAudioFile()
	{
		if (filename.empty() || hasSound)
			return;

		audioChunk = Mix_LoadWAV(filename.c_str());
		if (audioChunk)
			hasSound = true;
	}
}
