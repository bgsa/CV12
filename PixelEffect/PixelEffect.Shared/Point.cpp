#include <cstdlib>

#include "Log.h"
#include "Shader.h"
#include "Point.h"

PointShaderAttributes pointAttributes = PointShaderAttributes {
	{ //position 
		0.0f, 0.0f, 0.0f
	},
	{ //color 
		1.0f, 0.0f, 0.0f, 1.0f
	}
};

void Point::setPointSize(float newPointSize) 
{
	pointSize = newPointSize;
}

void Point::init()
{
	const char* vertexShaderSource = "#version 300 es \n"
		"uniform mat4 modelView; \n"
		"uniform mat4 projectionView; \n"
		"uniform float pointSize; \n"

		"in  vec3 Position; \n"
		"in  vec4 Color; \n"

		"out vec4 fragmentColor; \n"

		"void main() \n"
		"{											\n"
		"	gl_Position = projectionView * modelView * vec4(Position, 1.0); \n"
		"   gl_PointSize = pointSize;   \n"
		"	fragmentColor = Color; \n"
		"}											\n";

	const char* fragmentShaderSource = "#version 300 es \n"
		"precision mediump float; \n"
		"in  vec4 fragmentColor; \n"
		"out vec4 FragColor; \n"

		"void main() \n"
		"{\n"
		"	FragColor = fragmentColor; \n"
		"}";
	

	this->attributes = pointAttributes;

	programShader = Shader::loadShaderProgram(vertexShaderSource, fragmentShaderSource);

	initVBO();
}

void Point::setUpPositionAttribute()
{
	glVertexAttribPointer(positionAttribute,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0); //Specify that our coordinate data is going into attribute index 0(shaderAttribute), and contains three floats per vertex
	glEnableVertexAttribArray(positionAttribute); //habilita atributo de coordenadas
}

void Point::setUpColorAttribute()
{
	glVertexAttribPointer(colorAttribute,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)(sizeof(attributes.position)) // deslocamento do primeiro elemento
	);
	glEnableVertexAttribArray(colorAttribute); //habilita atributo de coordenadas
}

void Point::initVBO()
{
	glGenBuffers(1, &pointVBO);  //aloca o buffr
	glBindBuffer(GL_ARRAY_BUFFER, pointVBO); //associa o bufffer ao ponteiro
	glBufferData(GL_ARRAY_BUFFER, sizeof(PointShaderAttributes), &attributes, GL_STATIC_DRAW);  //insere os dados no buffer para usar glDraw*
																							 // Get the sampler location
	modelViewLocation = glGetUniformLocation(programShader, "modelView");
	projectionLocation = glGetUniformLocation(programShader, "projectionView");
	positionAttribute = glGetAttribLocation(programShader, "Position");
	colorAttribute = glGetAttribLocation(programShader, "Color");
	pointSizeLocation = glGetUniformLocation(programShader, "pointSize");

	setUpPositionAttribute();
	setUpColorAttribute();
}

void Point::render(Mat4f projectionViewMatrix)
{
	glUseProgram(programShader);

	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);

	glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelView);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionViewMatrix);

	glUniform1fv(pointSizeLocation, 1, &pointSize);

	setUpPositionAttribute();
	setUpColorAttribute();

	glDrawArrays(GL_POINTS, 0, 1);
}

Point::~Point()
{
	if (programShader != 0)
		glDeleteProgram(programShader);

	if (pointVBO != 0)
		glDeleteBuffers(1, &pointVBO);
}