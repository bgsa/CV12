#pragma once

#include "GlobalHeader.h"

struct PointShaderAttributes {
	GLfloat position[3];
	GLfloat color[4];
};

class Point
{
private:
	Mat4f modelView = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	GLuint programShader;
	PointShaderAttributes attributes;

	GLuint pointVBO;

	GLint modelViewLocation;
	GLint projectionLocation;
	GLint positionAttribute;
	GLint colorAttribute;
	GLint pointSizeLocation;

	float pointSize = 3.0f;

	void initVBO();
	void setUpPositionAttribute();
	void setUpColorAttribute();

public:
	~Point();

	void init();

	void setPointSize(float newPointSize);

	void render(Mat4f projectionViewMatrix);
};
