#pragma once

#include <map>

using namespace std;

struct TouchPosition {
	float x;
	float y;
};

struct TouchEvent {
	int pointerId;
	float pointerSize;
	TouchPosition position;
};

struct TouchItem {
	int pointerId;
	float pointerSize;
	TouchPosition initialPosition;
	TouchPosition previousPosition;
	TouchPosition currentPosition;
};

class TouchInputDeviceHandler
{
private:
	map<int, TouchItem*> *touchItems;

public:
	void updateTouchItems(map<int, TouchItem*> *touchItems) {
		this->touchItems = touchItems;
	}

	map<int, TouchItem*> *getTouchPointers() {
		return touchItems;
	}

	virtual void onTouchPointerIn(TouchEvent e) {};
	virtual void onTouchPointerOut(TouchEvent e) {};

	virtual void onTouchDown(TouchItem* touchItem) {};
	virtual void onTouchUp(TouchItem* touchItem) {};
	virtual void onTouchMove(TouchItem* touchItem) {};
};
