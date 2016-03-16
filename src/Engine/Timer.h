#pragma once
#include "Object.h"

#include <stdint.h>
#include <math.h>
#include <functional>

using Time = uint32_t;

class Timer : public Object
{
public:
	Timer();

	static Time FloatToTime(float val)
	{
		return (Time)round(val*1000.f);
	}

	// Actions
	virtual void Start();
	virtual void Stop();
	virtual void Pause();
	virtual void Resume();
	virtual void Reset();
	Time GetTickCount();

	bool IsStarted();
	bool IsActive();
	bool IsPaused();

	std::function<Time(void)> GetCurrentTicks;
	//uint32_t (*GetCurrentTicks)(void);
protected:
	Time StartTicks, PausedTicks;
	bool bPaused, bStarted;
};


#include <vector>
#include <algorithm>
#include <functional>

// Must be implemented inside main loop too!
class VolumeTimer : public Timer
{
public:
	VolumeTimer() : Timer()
	{
		VolumeTimers.push_back(this);
	}
	virtual ~VolumeTimer()
	{
		Erase();
	}

	virtual void Start(float seconds)
	{
		Super::Start();
		TimeLimit = seconds;
	}

	virtual void Erase()
	{
		VolumeTimers.erase(
			std::remove_if(VolumeTimers.begin(), VolumeTimers.end(),
	            [&] (VolumeTimer* vt)
	            {
	                return vt == this;
	            }),
	        	VolumeTimers.end()
	    	);
	}

	virtual Time GetTimeLimit()
	{
		return Timer::FloatToTime(TimeLimit);
	}

	virtual float GetProportionalTime()
	{
		return (float)(GetCurrentTicks()/GetTimeLimit());
	}

	virtual void Destroy()
	{
		delete this;
	}

	float TimeLimit;
	// Needs to be an std::function to lambda capture correctly. (Very important)
	std::function<void(float, float)> Function;
	//void (*Function)(VolumeTimer*, float, float);

	static void TimerTick(float dt)
	{
		for(VolumeTimer* vt : VolumeTimers)
		{
			if(vt != nullptr)
			{
				if(vt->IsActive())
				{
					if(vt->GetTickCount() >= (uint32_t)(vt->TimeLimit*1000.f))
					{
						float vtdt = (float)(vt->GetTickCount()/1000.f) - vt->TimeLimit;
						if(vt->Function)
						{
							vt->Function(vtdt, vt->TimeLimit);
						}
					}
				}
			}
			else
			{
				VolumeTimers.erase(std::remove(VolumeTimers.begin(), VolumeTimers.end(), vt), VolumeTimers.end());
			}
		}
	}

	static std::vector<VolumeTimer*> VolumeTimers;
private:
	using Super = Timer;
};
