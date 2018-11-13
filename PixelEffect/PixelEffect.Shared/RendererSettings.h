#pragma once

#include "GlobalHeader.h"
#include "ColorRGBA.h"
#include <OpenML/Point2D.h>
#include <OpenML/Rectangle2D.h>

class RendererSettings
{
private:
	RendererSettings();

	int width, height;
	OpenML::Point2Df screenPosition;
	ColorRGBAc backgroundColor = { 128, 128, 128, 255 }; //gray backgtound color

public:

	OpenML::Point2Df getScreenPosition();
	void setScreenPosition(OpenML::Point2Df position);

	OpenML::Rectangle2Df getScreenBound();
	
	int getWidth();
	void setWidth(int width);

	int getHeight();
	void setHeight(int height);

	float getAspectRatio();

	ColorRGBAc getBackgroudColor();
	void setBackgroudColor(ColorRGBAc color);

	API_INTERFACE static RendererSettings* getInstance();

};
