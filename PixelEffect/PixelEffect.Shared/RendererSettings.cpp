#include "RendererSettings.h"

RendererSettings* instanceRendererSettings;

RendererSettings::RendererSettings()
{
}

RendererSettings* RendererSettings::getInstance()
{
	if (instanceRendererSettings == nullptr)
		instanceRendererSettings = new RendererSettings;

	return instanceRendererSettings;
}

OpenML::Rectangle2Df RendererSettings::getScreenBound()
{
	return OpenML::Rectangle2Df(
		Vec2f(0.0f, 0.0f),
		Vec2f(float(width), 0.0f),
		Vec2f(float(width), float(height)),
		Vec2f(0.0f, float(height))
	);
}

OpenML::Point2Df RendererSettings::getScreenPosition()
{
	return screenPosition;
}
void RendererSettings::setScreenPosition(OpenML::Point2Df position)
{
	screenPosition = position;
}

int RendererSettings::getWidth() 
{
	return width;
}
void RendererSettings::setWidth(int width) 
{
	this->width = width;
}

int RendererSettings::getHeight() 
{
	return height;
}
void RendererSettings::setHeight(int height) 
{
	this->height = height;
}

float RendererSettings::getAspectRatio() 
{
	return (float) (getWidth() / getHeight());
}

ColorRGBAc RendererSettings::getBackgroudColor()
{
	return backgroundColor;
}
void RendererSettings::setBackgroudColor(ColorRGBAc color)
{
	this->backgroundColor = color;
}
