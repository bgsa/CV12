#pragma once

class InputDevice
{
public:
	
	virtual void update(long long elapsedTime) = 0;

	virtual ~InputDevice() {}

};

