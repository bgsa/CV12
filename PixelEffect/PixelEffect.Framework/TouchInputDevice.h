#pragma once

#include "InputDevice.h"
#include "TouchInputDeviceHandler.h"

class TouchInputDevice : public InputDevice
{
public:

	virtual void addHandler(TouchInputDeviceHandler* handler) = 0;
	virtual void removeHandler(TouchInputDeviceHandler* handler) = 0;

};