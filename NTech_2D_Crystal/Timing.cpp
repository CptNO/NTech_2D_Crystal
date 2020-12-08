#include "Timing.h"

namespace NTCrystal
{

	FpsLimiter::FpsLimiter()
	{}

	void FpsLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	void FpsLimiter::setMaxFPS(float maxFPS)
	{
		m_maxFPS = maxFPS;
	}

	void FpsLimiter::begin()
	{
		m_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::end()
	{
		calculateFPS();

		float frameTicks = SDL_GetTicks() - m_startTicks;
		//limit fps to max fps

		if ((1000.0f / m_maxFPS) > frameTicks)
		{
			SDL_Delay((1000.0f / m_maxFPS) - frameTicks);
		}

		return m_fps;
	}

	void FpsLimiter::calculateFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;



		static float prevTicks = SDL_GetTicks();

		float currentTicks;
		currentTicks = SDL_GetTicks();

		m_frameTime = currentTicks - prevTicks;

		frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

		prevTicks = currentTicks;

		int count;

		if (currentFrame < NUM_SAMPLES){
			count = currentFrame;
		}
		else{
			count = NUM_SAMPLES;
		}

		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++){
			frameTimeAverage += frameTimes[i];
		}

		frameTimeAverage /= count;

		if (frameTimeAverage > 0){
			m_fps = 1000.0f / frameTimeAverage;
		}
		else{
			m_fps = 60.0f;
		}

		currentFrame++;
	}
}