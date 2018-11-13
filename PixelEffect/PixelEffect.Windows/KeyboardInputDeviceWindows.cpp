#include "KeyboardInputDeviceWindows.h"

vector<KeyboardInputDeviceHandler*> handlersKeyboard;
GLFWwindow* keyboardWindow;

void onKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		for ( KeyboardInputDeviceHandler* handler : handlersKeyboard)
			handler->onKeyDown(key);

	if (action == GLFW_RELEASE)
		for (KeyboardInputDeviceHandler* handler : handlersKeyboard)
			handler->onKeyUp(key);
}

bool isKeyPressedA(int virtualKey)
{
	int state = glfwGetKey(keyboardWindow, virtualKey);

	return state == GLFW_PRESS;
}

void KeyboardInputDeviceWindows::init(GLFWwindow* window)
{
	this->window = window;
	keyboardWindow = window;

	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1); // for pooling do not lose any event

	glfwSetKeyCallback(window, onKeyboardEvent);
}

void KeyboardInputDeviceWindows::addHandler(KeyboardInputDeviceHandler* handler)
{
	handler->init(&isKeyPressedA);
	handlersKeyboard.push_back(handler);
}

void KeyboardInputDeviceWindows::removeHandler(KeyboardInputDeviceHandler* handler)
{
	vector<KeyboardInputDeviceHandler*>::iterator item = std::find(handlersKeyboard.begin(), handlersKeyboard.end(), handler);

	if (item != handlersKeyboard.end())
		handlersKeyboard.erase(item);
}

void KeyboardInputDeviceWindows::update(long long elapsedTime)
{

}

bool KeyboardInputDeviceWindows::isKeyPressed(int virtualKey)
{
	return isKeyPressedA(virtualKey);
}
