#pragma once

#include <chrono>

using namespace std::chrono;

typedef high_resolution_clock Clock;

class Timer
{
private:
	high_resolution_clock::time_point timeLastFrame;
	milliseconds deltaTime;
	int framesPerSecond;

	void calculateFramesPerSecond();
	
public:
	void start();
	void update();

	long long getElapsedTime();
	int getFramesPerSecond();
};

