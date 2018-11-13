#include "Line.h"

#include <cstdlib>
#include "Shader.h"
#include "GLConfig.h"

LineShaderAttributes lineAttributes = LineShaderAttributes {
	//position 
	{ 0.f, 0.f, 0.0f },
	{ 10.f, 10.f, 0.0f },
	//color 
	{ 1.0f, 0.0f, 0.0f, 1.0f },
	{ 1.0f, 0.0f, 0.0f, 1.0f }
};

void Line::setLineWidth(float newLineWidth)
{
	lineWidth = newLineWidth;
}

void Line::init()
{
	const char* vertexShaderSource = "#version 300 es \n"
		"uniform mat4 modelView; \n"
		"uniform mat4 projectionView; \n"

		"in  vec3 Position; \n"
		"in  vec4 Color; \n"

		"out vec4 fragmentColor; \n"

		"void main() \n"
		"{											\n"
		"	gl_Position = projectionView * modelView * vec4(Position, 1.0); \n"
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
	
	this->attributes = lineAttributes;

	programShader = Shader::loadShaderProgram(vertexShaderSource, fragmentShaderSource);

	initVBO();
}

void Line::setUpPositionAttribute()
{
	glVertexAttribPointer(positionAttribute,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0); //Specify that our coordinate data is going into attribute index 0(shaderAttribute), and contains three floats per vertex
	glEnableVertexAttribArray(positionAttribute); //habilita atributo de coordenadas
}

void Line::setUpColorAttribute()
{
	glVertexAttribPointer(colorAttribute,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)(sizeof(attributes.point1) + sizeof(attributes.point2)) // deslocamento do primeiro elemento
	);
	glEnableVertexAttribArray(colorAttribute); //habilita atributo de coordenadas
}

void Line::initVBO()
{
	glGenBuffers(1, &lineVBO);  //aloca o buffr
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO); //associa o bufffer ao ponteiro
	glBufferData(GL_ARRAY_BUFFER, sizeof(LineShaderAttributes), &attributes, GL_STATIC_DRAW);  //insere os dados no buffer para usar glDraw*
																								// Get the sampler location
	modelViewLocation = glGetUniformLocation(programShader, "modelView");
	projectionViewLocation = glGetUniformLocation(programShader, "projectionView");
	positionAttribute = glGetAttribLocation(programShader, "Position");
	colorAttribute = glGetAttribLocation(programShader, "Color");

	setUpPositionAttribute();
	setUpColorAttribute();
}

void Line::render(Mat4f projectionViewMatrix)
{
	glUseProgram(programShader);

	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);

	glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelView);
	glUniformMatrix4fv(projectionViewLocation, 1, GL_FALSE, projectionViewMatrix);
	
	setUpPositionAttribute();
	setUpColorAttribute();

	float currentLineWidth = GLConfig::getGLfloat(GL_LINE_WIDTH);
	glLineWidth(lineWidth);

	glDrawArrays(GL_LINES, 0, 2);

	glLineWidth(currentLineWidth);
}

Line::~Line()
{
	if (programShader != 0)
		glDeleteProgram(programShader);

	if (lineVBO != 0)
		glDeleteBuffers(1, &lineVBO);
}