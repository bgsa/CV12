#pragma once

//#include <Windows.h>
#include <DisplayDevice.h>
#include <GlobalHeader.h>

class DisplayDeviceWindow : public DisplayDevice
{
private:
	GLFWwindow* window;

public:
	void init(GLFWwindow* window);
	void swapBuffer() override;
};

