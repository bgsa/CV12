#include "PointerInputDeviceWindows.h"

GLFWwindow* mouseWindow;
vector<PointerInputDeviceHandler*> handlersPointer;

void onClick(GLFWwindow* window, int button, int action, int mods)
{
	double posx, posy;
	glfwGetCursorPos(mouseWindow, &posx, &posy);

	int screenHeight = RendererSettings::getInstance()->getHeight();

	MouseEvent e;
	e.currentPosition = OpenML::Point2Df{ float(posx), screenHeight - float(posy) };

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		e.button = MouseButton::LEFT;
		break;

	case GLFW_MOUSE_BUTTON_RIGHT:
		e.button = MouseButton::RIGHT;
		break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
		e.button = MouseButton::MIDDLE;
		break;
	}

	if (action == GLFW_PRESS)
		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseDown(e);
	else
		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseUp(e);
}

void onMove(GLFWwindow* window, double posx, double posy)
{
	int screenHeight = RendererSettings::getInstance()->getHeight();

	MouseEvent e;
	e.currentPosition = OpenML::Point2Df{ float(posx), screenHeight - float(posy) };

	int leftButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_LEFT);
	int rightButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_RIGHT);
	int middleButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_MIDDLE);
	
	e.state = {
		e.currentPosition,
		leftButtonState == GLFW_PRESS, 
		rightButtonState == GLFW_PRESS,
		middleButtonState == GLFW_PRESS
	};

	for (PointerInputDeviceHandler* handler : handlersPointer)
		handler->onMouseMove(e);
}

MouseState getMouseState()
{
	double posx, posy;
	glfwGetCursorPos(mouseWindow, &posx, &posy);

	int screenHeight = RendererSettings::getInstance()->getHeight();
	OpenML::Point2Df position{ float(posx), screenHeight - float(posy) };

	int leftButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_LEFT);
	int rightButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_RIGHT);
	int middleButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_MIDDLE);

	bool leftButtonPressed = leftButtonState == GLFW_PRESS;
	bool rightButtonPressed = rightButtonState == GLFW_PRESS;
	bool middleButtonPressed = middleButtonState == GLFW_PRESS;

	return MouseState{ position, leftButtonPressed, rightButtonPressed, middleButtonPressed };
}

void onScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseState state = getMouseState();
	WheelDirection direction = WheelDirection::UP;

	if (xoffset == 0.0)
		if (yoffset > 0)
			direction = WheelDirection::UP;
		else
			direction = WheelDirection::DOWN;

	MouseEvent e;
	e.currentPosition = state.position;
	e.direction = direction;

	for (PointerInputDeviceHandler* handler : handlersPointer)
		handler->onWheel(e);
}

void PointerInputDeviceWindows::init(GLFWwindow* window)
{
	mouseWindow = window;

	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1); // for pooling do not lose event

	glfwSetMouseButtonCallback(window, onClick);
	glfwSetCursorPosCallback(window, onMove);
	glfwSetScrollCallback(window, onScroll);
}

void PointerInputDeviceWindows::addHandler(PointerInputDeviceHandler* handler) {
	handler->init(&getMouseState);
	handlersPointer.push_back(handler);
}

void PointerInputDeviceWindows::removeHandler(PointerInputDeviceHandler* handler) 
{
	vector<PointerInputDeviceHandler*>::iterator item = std::find(handlersPointer.begin(), handlersPointer.end(), handler);

	if (item != handlersPointer.end())
		handlersPointer.erase(item);
}

void PointerInputDeviceWindows::update(long long elapsedTime)
{
}
