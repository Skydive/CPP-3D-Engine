#include "Timer.h"

std::vector<VolumeTimer*> VolumeTimer::VolumeTimers;

Timer::Timer()
{
	//Initialise
	StartTicks = 0;
	PausedTicks = 0;
	bPaused = false;
	bStarted = false;
}

void Timer::Start()
{
	bStarted = true;
	bPaused = false;

	StartTicks = GetCurrentTicks();
	PausedTicks = 0;
}

void Timer::Stop()
{
	bStarted = false;
	bPaused = false;
	StartTicks = 0;
	PausedTicks = 0;
}

void Timer::Pause()
{
	if(bStarted && !bPaused)
	{
		bPaused = true;
		PausedTicks = GetCurrentTicks() - StartTicks;
		StartTicks = 0;
	}
}

void Timer::Resume()
{
	if( bStarted && bPaused )
	{
		bPaused = false;
		StartTicks = GetCurrentTicks() - PausedTicks;
		PausedTicks = 0;
	}
}

void Timer::Reset()
{
	StartTicks = 0;
	PausedTicks = 0;
	bPaused = false;
	bStarted = true;

	StartTicks = GetCurrentTicks();
	PausedTicks = 0;
}

uint32_t Timer::GetTickCount()
{
	if(bStarted)
	{
		if(bPaused)
		{
			return PausedTicks;
		}
		else
		{
			return GetCurrentTicks() - StartTicks;
		}
	}
	return 0;
}

bool Timer::IsStarted()
{
	return bStarted;
}
bool Timer::IsActive()
{
	return bStarted && !bPaused;
}
bool Timer::IsPaused()
{
	return bStarted && bPaused;
}
