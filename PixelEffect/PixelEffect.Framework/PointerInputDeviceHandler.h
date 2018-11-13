#pragma once

#include <OpenML/Point2D.h>
#include "RendererSettings.h"

enum MouseButton {
	LEFT,
	RIGHT,
	MIDDLE
};

enum WheelDirection {
	UP,
	DOWN
};

struct MouseState {
	OpenML::Point2Df position;
	bool leftButtonPressed;
	bool rightButtonPressed;
	bool middleButtonPressed;
};

struct MouseEvent {
	MouseButton button;	
	OpenML::Point2Df initialPosition;
	OpenML::Point2Df currentPosition;
	WheelDirection direction;
	MouseState state;
};

class PointerInputDeviceHandler
{
private:
	MouseState(*getMouseStateFunction)();

public:
	void init(MouseState(*getMouseStateFunction)()) {
		this->getMouseStateFunction = getMouseStateFunction;
	}

	MouseState getMouseState() {
		return getMouseStateFunction();
	}

	virtual void onMouseMove(MouseEvent e) {};
	
	virtual void onMouseDown(MouseEvent e) {};
	virtual void onMouseUp(MouseEvent e) {};

	virtual void onDoubleClick(MouseEvent e) {};

	virtual void onWheel(MouseEvent e) {}
};
