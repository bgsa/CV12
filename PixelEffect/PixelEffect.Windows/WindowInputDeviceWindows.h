#pragma once

#include <GlobalHeader.h>
#include <WindowInputDevice.h>
#include <algorithm>

using namespace std;

class WindowInputDeviceWindows : public WindowInputDevice
{
private:
	WindowInputDeviceWindows();

	GLFWwindow* window;
	vector<WindowInputDeviceHandler*> handlers;

public:

	API_INTERFACE static WindowInputDeviceWindows * getInstance();

	void init(GLFWwindow* window);
	void update(long long elapsedTime);

	void close();

	void addHandler(WindowInputDeviceHandler* handler);
	void removeHandler(WindowInputDeviceHandler* handler);
};

