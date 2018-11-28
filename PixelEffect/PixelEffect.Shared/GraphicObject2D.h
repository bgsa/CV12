#pragma once

#include "GlobalHeader.h"
#include "GLConfig.h"
#include "GraphicObject.h"
#include "RendererSettings.h"
#include <vector>
#include "ContentAlignment.h"

class GraphicObject2D : public GraphicObject 
{
private:

protected:
	ColorRGBAf* color = new ColorRGBAf{ 1.0f, 1.0f, 1.0f, 1.0f };
	ColorRGBAf* borderColor = new ColorRGBAf{ 1.0f, 0.0f, 1.0f, 1.0f };
	float borderWidth = 1.0f;
	GraphicObject2D* parentObject2D = nullptr;
	vector<GraphicObject2D*> childrenObject2D;
	ContentAlignment alignment;
	OpenML::Point2Df margin;

public:

	virtual GraphicObject2D* getParent() {
		return parentObject2D;
	}
	virtual void setParent(GraphicObject2D* parentObject) {
		parentObject2D = parentObject;
	}
	
	virtual OpenML::Point2Df getParentPosition()
	{
		OpenML::Point2Df parentPosition = { 0.0f , 0.0f };

		if (parentObject2D != nullptr)
			parentPosition = parentObject2D->getPosition();

		return parentPosition;
	}
	virtual OpenML::Point2Df getParentSize()
	{
		float parentWidth = float(RendererSettings::getInstance()->getWidth());
		float parentHeight = float(RendererSettings::getInstance()->getHeight());

		if (parentObject2D != nullptr) {
			parentWidth = parentObject2D->getWidth();
			parentHeight = parentObject2D->getHeight();
		}

		return OpenML::Point2Df(parentWidth, parentHeight);
	}

	virtual ColorRGBAf* getColor() {
		return color;
	}
	virtual void setColor(ColorRGBAf color) {
		this->color->Red = color.Red;
		this->color->Green = color.Green;
		this->color->Blue = color.Blue;
		this->color->Alpha = color.Alpha;
	}

	virtual Vec2f getPosition()
	{
		return { modelView[12], modelView[13] };
	}
	virtual void setPosition(Vec2f position)
	{
		modelView[12] = position.x();
		modelView[13] = position.y();
	}
	
	virtual void setBotomMargin(float bottomMargin)
	{
		assert(bottomMargin > 0);
		margin.y = bottomMargin;
	}
	virtual void setLeftMargin(float leftMargin)
	{
		assert(leftMargin > 0);
		margin.x = leftMargin;
	}

	virtual void setRelativeBottomMargin(float relativeBottomMargin)
	{
		assert(relativeBottomMargin > 0);

		OpenML::Point2Df parentSize = getParentSize();

		margin.y = parentSize.y * (relativeBottomMargin / 100);
	}
	virtual void setRelativeLeftMargin(float relativeLeftMargin)
	{
		assert(relativeLeftMargin > 0);

		OpenML::Point2Df parentSize = getParentSize();

		margin.x = parentSize.x * (relativeLeftMargin / 100);
	}

	virtual ContentAlignment getAlignment() 
	{
		return alignment;
	}
	virtual void setAlignment(ContentAlignment alignment) 
	{
		this->alignment = alignment;
	}

	virtual void verticalAlignToCenter()
	{
		alignment.vertical = VerticalAlignment::CENTER;

		OpenML::Point2Df parentSize = getParentSize();
		OpenML::Point2Df parentPosition = getParentPosition();

		float leftMargin = parentPosition.x + (parentSize.x / 2) - (getWidth() / 2);

		modelView[12] = leftMargin;
	}
	virtual void horizontalAlignToCenter()
	{
		alignment.horizontal = HorizontalAlignment::MIDDLE;

		OpenML::Point2Df parentSize = getParentSize();
		OpenML::Point2Df parentPosition = getParentPosition();

		float bottomMargin = parentPosition.y + (parentSize.y / 2) - (getHeight() / 2);

		modelView[13] = bottomMargin;
	}

	virtual float getWidth()
	{
		return modelView[0];
	}
	virtual void setWidth(float width)
	{
		modelView[0] = width;
	}
	virtual void setRelativeWidth(float relativeWidth)
	{
		assert(relativeWidth > 0);

		float windowWidth = float(RendererSettings::getInstance()->getWidth());
		modelView[0] = windowWidth * (relativeWidth / 100);
	}

	virtual float getHeight()
	{
		return modelView[5];
	}
	virtual void setHeight(float height)
	{
		modelView[5] = height;
	}
	virtual void setRelativeHeight(float relativeHeight)
	{
		assert(relativeHeight > 0);

		float windowHeight = float(RendererSettings::getInstance()->getHeight());
		modelView[5] = windowHeight * (relativeHeight / 100);
	}

	virtual void setSize(float width, float height)
	{
		setWidth(width);
		setHeight(height);
	}

	virtual float getBorderWidth()
	{
		return borderWidth;
	}
	virtual void setBorderWidth(float borderWidth)
	{
		this->borderWidth = borderWidth;
	}

	virtual void setBorderColor(ColorRGBAf color)
	{
		borderColor->Red = color.Red;
		borderColor->Green = color.Green;
		borderColor->Blue = color.Blue;
		borderColor->Alpha = color.Alpha;
	}
	virtual ColorRGBAf* getBorderColor()
	{
		return borderColor;
	}

	virtual void renderBorder(Mat4f projectionViewMatrix, size_t pointsCount)
	{
		if (borderWidth == 0.0f)
			return;

		glUniform4f(colorLocation, borderColor->Red, borderColor->Green, borderColor->Blue, borderColor->Alpha);

		float currentLineWidth = GLConfig::getGLfloat(GL_LINE_WIDTH);
		glLineWidth(borderWidth);

		glDrawArrays(GL_LINE_LOOP, 0, pointsCount);

		glLineWidth(currentLineWidth);
	}

	virtual ~GraphicObject2D() {
		delete color;
		delete borderColor;

		for (size_t i = 0; i < childrenObject2D.size(); i++)
			delete childrenObject2D[i];
	}

};