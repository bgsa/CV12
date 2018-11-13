#pragma once

#include "InputDevice.h"
#include "WindowInputDeviceHandler.h"

class WindowInputDevice : public InputDevice
{
public:

	virtual void addHandler(WindowInputDeviceHandler* handler) = 0;
	virtual void removeHandler(WindowInputDeviceHandler* handler) = 0;

};