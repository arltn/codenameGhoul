#include "Clock.h"
//Initializes variables
Clock::Clock()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mStarted = false;
	mPaused = false;
};

//The various clock actions
void Clock::start()
{
	mStarted = true;
	mPaused = false;
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
};
void Clock::stop()
{
	mStarted = false;
	mPaused = false;
	mStartTicks = 0;
	mPausedTicks = 0;
};
void Clock::pause()
{
	if (mStarted && !mPaused)
	{
		mPaused = true;
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
};
void Clock::unpause()
{
	if (mStarted && mPaused)
	{
		mPaused = false;
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
};

//Gets the timer's time
Uint32 Clock::getTicks()
{
	//actual timer time
	Uint32 time = 0;
	
	//if timer is running
	if (mStarted)
	{
		if (mPaused)
		{
			time = mPausedTicks;
		}
		else
		{
			Uint32 temp = SDL_GetTicks();
			time = temp - mStartTicks;
			//time = SDL_GetTicks() - mStartTicks;
		}
	}
	return time;
};

//Checks the status of the timer
bool Clock::isStarted(){ return mStarted; };
bool Clock::isPaused(){ return mPaused && mStarted; };