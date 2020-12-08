#pragma once

#include  <Windows.h>

namespace NTCrystal{
	class Timmer
	{
	public:
		Timmer();
		~Timmer();
		void reset();
		float elapsed();
	private:
		LARGE_INTEGER m_start;
		double m_frequency;

	};

	Timmer::Timmer()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		m_frequency = 1.0 / frequency.QuadPart;
		QueryPerformanceCounter(&m_start);
	}

	Timmer::~Timmer()
	{
	}

	void Timmer::reset()
	{
		QueryPerformanceCounter(&m_start);
	}

	float Timmer::elapsed()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - m_start.QuadPart;
		return (float)(cycles * m_frequency);
	}
}