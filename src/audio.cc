#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/components/audio_source.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace AsciiEngine
{
	void Engine::playAudioSource(AudioSource *source)
	{
		if (!audioInitialized)
			return;

		auto sound = source->getAudioChunk();
		if (sound != nullptr)
			Mix_PlayChannel(-1, sound, 0);
	}

	void Engine::initAudio()
	{
		if (audioInitialized)
			return;

		SDL_Init(SDL_INIT_AUDIO);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		audioInitialized = true;
	}

	void Engine::cleanAudio()
	{
		Mix_HaltChannel(-1);

		/* free all audio chunks in each component*/
		callOnAllActiveObjects([&](AsciiObject *ao) {
			auto audio = ao->getAllComponentsOfType<AudioSource>();

			for (auto *src : audio)
				src->freeChunk();
		});

		Mix_CloseAudio();
		SDL_Quit();
	}
}
