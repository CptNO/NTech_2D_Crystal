#include <SDL.h>

#pragma once

namespace NTCrystal
{

	class FpsLimiter
	{
	public:
		FpsLimiter();

		void setMaxFPS(float maxFPS);

		void init(float maxFPS);

		void begin();

		float end();

	private:

		void calculateFPS();

		float m_maxFPS;
		float m_fps;
		float m_frameTime;

		unsigned int m_startTicks;
	};
}