#pragma once

class KeyboardInputDeviceHandler
{
private:
	bool(*isKeyPressedFunction)(int);

public:	
	void init( bool(*isKeyPressedFunction)(int)   ) {
		this->isKeyPressedFunction = isKeyPressedFunction;
	}

	bool isKeyPressed(int keyCode) 
	{
		return isKeyPressedFunction(keyCode);
	}

	virtual void onKeyDown(int keyCode) {};
	virtual void onKeyUp(int keyCode) {};
};

