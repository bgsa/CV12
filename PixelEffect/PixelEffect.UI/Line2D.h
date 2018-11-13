#pragma once

#include "GlobalHeader.h"
#include <vector>
#include <OpenML/Point2D.h>
#include "Point2D.h"
#include <OpenML/Orientation.h>
#include <OpenML/Line2D.h>
#include "GraphicObject2D.h"

class Line2D : public GraphicObject2D
{
private:

	struct Line2DShaderAttributes {
		GLfloat point1[2];
		GLfloat point2[2];
	};
	
	Line2DShaderAttributes attributes = Line2DShaderAttributes{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f }
	};


	GLint positionAttribute;	
	float lineWidth = 3.0f;

	void initVBO();
	void setUpPositionAttribute();

public:
	void init();

	OpenML::Point2Df getPoint1();
	void setPoint1(OpenML::Point2Df position);

	OpenML::Point2Df getPoint2();
	void setPoint2(OpenML::Point2Df position);

	void setLineWidth(float newLineWidth);

	/// <summary>
	/// Indicate whether the point is ON the vector
	/// It means the point is a point on this line
	/// </summary>
	bool isOnTheLine(OpenML::Point2Df point);

	/// <summary>
	/// Indicate whether the point is on the left of the vector/line
	/// </summary>
	bool isOnTheLeft(OpenML::Point2Df point);

	/// <summary>
	/// Indicate whether the point is on the right of the vector/line
	/// </summary>
	bool isOnTheRight(OpenML::Point2Df point);

	/// <summary>
	/// Indicate whether the point is on the left, right or is a point of the line line/vector
	/// </summary>
	OpenML::VerticalOrientation getOrientation(OpenML::Point2Df point);

	OpenML::Point2Df* findIntersection(Line2D* otherLine);
	float getDistance(Point2D point);
	float getDistance(OpenML::Point2Df position);

	Vec3f getEquation();
	
	float deltaX();
	float deltaY();

	void render(Mat4f projectionViewMatrix);

	OpenML::Line2Df toOpenMLLine2D() 
	{
		return OpenML::Line2Df(attributes.point1, attributes.point2);
	}

	string toString() {
		return "Line 2D";
	}
};
