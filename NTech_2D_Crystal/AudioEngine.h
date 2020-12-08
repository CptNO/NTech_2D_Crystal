#pragma once

#include <SDL_mixer.h>
#include <string>
#include <map>

namespace NTCrystal{


	class SoundEffect
	{
	public:
		friend class AudioEngine;

		SoundEffect() :m_chunk(nullptr){}

		///Plays effect file
		///-1 repeat forever, 0 play one time, 1 play one time
		void play(int loops = 0);
		void stop();

	private:

		Mix_Chunk* m_chunk;

	};

	class Music
	{
	public:

		friend class AudioEngine;

		Music() :m_music(nullptr){}

		///plays music file
		///-1 repeat forever, 0 don't play, 1 play one time
		void play(int loop = -1);
		static void pause();
		static void stop();
		static void resume();

	private:
		Mix_Music* m_music;
	};

	//meanger for music and sound effects
	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy(); //release all the reasorces

		SoundEffect loadSoundEffect(const std::string &filePath);
		Music loadMusic(const std::string &filePath);


	private:

		std::map<std::string, Mix_Chunk*> m_effectMap;
		std::map<std::string, Mix_Music*> m_musicMap;

		bool m_isInitialized = false;
	};
}
