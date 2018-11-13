#pragma once

#include "InputDevice.h"
#include "KeyboardInputDeviceHandler.h"

class KeyboardInputDevice : public InputDevice
{
public:

	virtual void addHandler(KeyboardInputDeviceHandler* handler) = 0;
	virtual void removeHandler(KeyboardInputDeviceHandler* handler) = 0;

};