#pragma once

#include "AsciiEngine/core/component.hpp"
#include <string>
#include <SDL2/SDL_mixer.h>

namespace AsciiEngine
{
	struct AudioSource : Component {
		std::string name;

		const std::string &getFilename() const { return filename; }

		Mix_Chunk *getAudioChunk();

		/*
		 * free audio chunk memory
		 */
		void freeChunk();

		AudioSource(const std::string &file);
		AudioSource(const std::string &name, const std::string &file);

	private:
		std::string filename;
		Mix_Chunk *audioChunk;
		bool hasSound = false;
	};
}
