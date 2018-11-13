#include "WindowInputDeviceWindows.h"

WindowInputDeviceWindows* instanceKeyboardDevice;

WindowInputDeviceWindows::WindowInputDeviceWindows()
{
}

WindowInputDeviceWindows * WindowInputDeviceWindows::getInstance()
{
	if (instanceKeyboardDevice == nullptr)
		instanceKeyboardDevice = new WindowInputDeviceWindows;

	return instanceKeyboardDevice;
}

static void onClose(GLFWwindow* window)
{
	if (instanceKeyboardDevice != nullptr)
		instanceKeyboardDevice->close();
}

void WindowInputDeviceWindows::init(GLFWwindow* window)
{
	this->window = window;

	//glfwSetWindowSizeCallback(window, onWindowResize);

	//glfwSetWindowPos(window, positionX, positionY);

	//glfwSetWindowPosCallback(window, onWindowMove);

	glfwSetWindowCloseCallback(window, onClose);

}

void WindowInputDeviceWindows::addHandler(WindowInputDeviceHandler* handler)
{
	handlers.push_back(handler);
}

void WindowInputDeviceWindows::removeHandler(WindowInputDeviceHandler* handler)
{
	vector<WindowInputDeviceHandler*>::iterator item = find(handlers.begin(), handlers.end(), handler);

	if (item != handlers.end())
		handlers.erase(item);
}

void WindowInputDeviceWindows::update(long long elapsedTime)
{
}

void WindowInputDeviceWindows::close() {
	for (size_t i = 0; i < handlers.size(); i++)
		handlers[i]->onClose();
}
