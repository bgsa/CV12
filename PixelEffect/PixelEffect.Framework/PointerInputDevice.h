#pragma once

#include "InputDevice.h"
#include "PointerInputDeviceHandler.h"

class PointerInputDevice : public InputDevice
{
public:

	virtual void addHandler(PointerInputDeviceHandler* handler) = 0;
	virtual void removeHandler(PointerInputDeviceHandler* handler) = 0;

};