#pragma once

#include "GlobalHeader.h"

struct LineShaderAttributes {
	GLfloat point1[3];	
	GLfloat point2[3];
	GLfloat pointColor1[4];
	GLfloat pointColor2[4];
};

class Line
{
private:
	Mat4f modelView = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	GLuint programShader;
	LineShaderAttributes attributes;

	GLuint lineVBO;

	GLint modelViewLocation;
	GLint projectionViewLocation;
	GLint positionAttribute;
	GLint colorAttribute;

	float lineWidth = 3.0f;

	void initVBO();
	void setUpPositionAttribute();
	void setUpColorAttribute();

public:
	~Line();

	void init();

	void setLineWidth(float newLineWidth);

	void render(Mat4f projectionViewMatrix);
};
