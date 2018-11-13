#pragma once

#include <GlobalHeader.h>
#include <KeyboardInputDevice.h>
#include <algorithm>

using namespace std;

class KeyboardInputDeviceWindows : public KeyboardInputDevice
{
private:
	GLFWwindow* window;
	
public:
	void init(GLFWwindow*);
	void update(long long elapsedTime);

	bool isKeyPressed(int virtualKey);

	void addHandler(KeyboardInputDeviceHandler* handler);
	void removeHandler(KeyboardInputDeviceHandler* handler);
};

