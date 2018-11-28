#pragma once

#include "GlobalHeader.h"
#include "Log.h"
#include "DisplayDevice.h"
#include "WindowInputDevice.h"
#include "KeyboardInputDevice.h"
#include "PointerInputDevice.h"
#include "TouchInputDevice.h"
#include <vector>
#include "GraphicObject.h"

class Renderer : public KeyboardInputDeviceHandler, public WindowInputDeviceHandler, public TouchInputDeviceHandler, public PointerInputDeviceHandler
{
private:
	vector<GraphicObject*> graphicObjects;

protected:
	DisplayDevice* displayDevice;
	vector<PointerInputDevice*> pointerInputDevices;
	vector<WindowInputDevice*> windowInputDevices;
	vector<KeyboardInputDevice*> keyboardInputDevices;
	vector<TouchInputDevice*> touchInputDevices;

	void render2D(Mat4f projectionViewMatrix);
	void render3D(Mat4f projectionViewMatrix);

public:
	float homeworkMode = 1.0f;
	int step = 1;
	bool isDebug = false;

	void init(DisplayDevice* displayDevice);
	void start();
	void resize(int width, int height);
	
	OpenML::Line2Df* getVanishLine();

	void update();
	void render();
	void exit();

	void addGraphicObject(GraphicObject* graphicObject);
	void removeGraphicObject(GraphicObject* graphicObject);

	void addInputDevice(InputDevice* inputDevice);

	void updateInputDevices(long long elapsedTime);

	virtual void onKeyDown(int keyCode);

	virtual void onMouseDown(MouseEvent e);
	virtual void onMouseUp(MouseEvent e);
	virtual void onMouseMove(MouseEvent e);

	void onKeyUp(int keyCode);
	void onClose();
	
	void onTouchPointerIn(TouchEvent e);
	void onTouchPointerOut(TouchEvent e);
	void onTouchDown(TouchItem* touchItem);
	void onTouchUp(TouchItem* touchItem);
	void onTouchMove(TouchItem* touchItem);

	~Renderer();
};

