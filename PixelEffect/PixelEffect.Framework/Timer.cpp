#include "Timer.h"

int timeCounter = 0;
int fpsCounter = 0;

void Timer::calculateFramesPerSecond() 
{
	bool oneSecondPassed = timeCounter > 1000;

	if (oneSecondPassed)
	{
		framesPerSecond = fpsCounter;
		timeCounter = 0;
		fpsCounter = 0;
	}

	timeCounter += (int) getElapsedTime();
	fpsCounter ++;
}

void Timer::start()
{
	timeLastFrame = Clock::now();
}

void Timer::update()
{
	high_resolution_clock::time_point currentTime = Clock::now();
	
	deltaTime = duration_cast<milliseconds>(currentTime - timeLastFrame);

	timeLastFrame = currentTime;

	calculateFramesPerSecond();
}

long long Timer::getElapsedTime()
{
	return deltaTime.count();
}

int Timer::getFramesPerSecond()
{
	return framesPerSecond;
}