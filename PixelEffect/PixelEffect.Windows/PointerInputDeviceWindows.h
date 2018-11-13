#pragma once

#include <GlobalHeader.h>
#include <PointerInputDevice.h>
#include <PointerInputDeviceHandler.h>
#include <algorithm>

using namespace std;

class PointerInputDeviceWindows : public PointerInputDevice
{
private:
	
public:
	void init(GLFWwindow* window);
	void update(long long elapsedTime);
	
	void addHandler(PointerInputDeviceHandler* handler);
	void removeHandler(PointerInputDeviceHandler* handler);
};

