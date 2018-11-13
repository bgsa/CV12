#pragma once

class DisplayDevice
{
private:
	int width;
	int height;

protected:
	void setWidth(int width);
	void setHeight(int height);

public:
	int getWidth();
	int getHeight();

	virtual void swapBuffer() {};

	virtual ~DisplayDevice() {}
};
