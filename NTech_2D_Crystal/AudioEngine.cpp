#include "AudioEngine.h"
#include "NTErrors.h"


namespace NTCrystal{
	AudioEngine::AudioEngine()
	{
		//Empty
	}


	AudioEngine::~AudioEngine()
	{
		destroy();
	}

	void AudioEngine::init()
	{
		if (m_isInitialized)
		{
			fatalError("Audio engine already init \n");
		}
		//Paramater can be bivise combination MIX_INI_FAC, MIX_INIT_MP3...
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1){
			fatalError("Mix init error, " + std::string(Mix_GetError()));
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY * 2, MIX_DEFAULT_FORMAT, 2, 2048)){
			fatalError("Mix init error, " + std::string(Mix_GetError()));
		}

		m_isInitialized = true;

	}

	void AudioEngine::destroy()
	{
		if (m_isInitialized == true)
		{
			m_isInitialized = true;

			for each (auto &it in m_effectMap)
			{
				Mix_FreeChunk(it.second);
			}

			for each (auto &it in m_musicMap)
			{
				Mix_FreeMusic(it.second);
			}
			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	NTCrystal::SoundEffect AudioEngine::loadSoundEffect(const std::string &filePath)
	{
		SoundEffect effect;

		//check if file aleready exists in chace 
		auto it = m_effectMap.find(filePath);

		if (it == m_effectMap.end())
		{
			Mix_Chunk *chunk = Mix_LoadWAV(filePath.c_str());
			if (chunk == nullptr){
				fatalError("Sound Effect not found: " + filePath);
			}

			effect.m_chunk = chunk;
			m_effectMap[filePath] = chunk;
		}
		else
		{
			effect.m_chunk = it->second;
		}

		return effect;
	}

	NTCrystal::Music AudioEngine::loadMusic(const std::string &filePath)
	{
		Music music;

		///check if file aleready exists in chace 
		auto it = m_musicMap.find(filePath);

		if (it == m_musicMap.end())
		{
			Mix_Music *mixMusic = Mix_LoadMUS(filePath.c_str());

			if (mixMusic == nullptr){
				fatalError("Music not found: " + filePath);
			}

			music.m_music = mixMusic;
			m_musicMap[filePath] = mixMusic;
		}
		else
		{
			music.m_music = it->second;
		}

		return music;
	}

	void SoundEffect::play(int loops/*=0*/)
	{
		///last parametar: -1 loop forever, 0 once, 1 etc
		///this will also return chanel what is needed for pausing sound etc
		if (Mix_PlayChannel(-1, m_chunk, loops) == -1)
		{
			fatalError("Faild to play sound effect: " + std::string(Mix_GetError()));
		}
	}

	void Music::play(int loop /*=-1*/)
	{
		if (Mix_PlayMusic(m_music,loop))
		{
			fatalError("Failed to play music: " + std::string(Mix_GetError()));
		}
	}

	void Music::pause()
	{
		Mix_ResumeMusic();
	}

	void Music::stop()
	{
		Mix_HaltMusic();
	}

	void Music::resume()
	{
		Mix_ResumeMusic();
	}

}
