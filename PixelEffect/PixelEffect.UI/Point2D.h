#pragma once

#include "GlobalHeader.h"
#include <OpenML/Point2D.h>
#include "ColorRGBA.h"

#include "GraphicObject2D.h"

namespace pxe {
	class Point2D : public GraphicObject2D
	{
	private:
		GLfloat position[2];

		GLint positionAttribute;
		GLint pointSizeLocation;

		float pointSize = 3.0f;

		void initVBO();
		void setUpPositionAttribute();

	public:
		Point2D();
		Point2D(OpenML::Point2Df point);

		void init();

		float getPointSize();
		void setPointSize(float newPointSize);

		Vec2f getPosition();
		void setPosition(Vec2f position);

		void render(Mat4f projectionViewMatrix);

		string toString() {
			return "Point 2D";
		}
	};

}