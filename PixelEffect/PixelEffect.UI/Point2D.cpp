#include <cstdlib>

#include "Shader.h"
#include "Point2D.h"

namespace pxe
{
	Vec2f Point2D::getPosition()
	{
		return Vec2f( position[0], position[1] );
	}
	void Point2D::setPosition(Vec2f position)
	{
		this->position[0] = position.x();
		this->position[1] = position.y();
	}

	float Point2D::getPointSize()
	{
		return pointSize;
	}
	void Point2D::setPointSize(float newPointSize)
	{
		pointSize = newPointSize;
	}

	void Point2D::init()
	{
		const char* vertexShaderSource = "#version 300 es \n"
			"uniform mat4 modelView; \n"
			"uniform mat4 projectionView; \n"
			"uniform vec4 Color; \n"
			"uniform float pointSize; \n"

			"in  vec2 Position; \n"

			"out vec4 fragmentColor; \n"

			"void main() \n"
			"{											\n"
			"	gl_Position = projectionView * modelView * vec4(Position, 0.0, 1.0); \n"
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


		programShader = Shader::loadShaderProgram(vertexShaderSource, fragmentShaderSource);

		initVBO();
	}

	void Point2D::setUpPositionAttribute()
	{
		glVertexAttribPointer(positionAttribute,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			0); //Specify that our coordinate data is going into attribute index 0(shaderAttribute), and contains three floats per vertex
		glEnableVertexAttribArray(positionAttribute); //habilita atributo de coordenadas
	}

	void Point2D::initVBO()
	{
		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(position), &position, GL_DYNAMIC_DRAW);

		modelViewLocation = glGetUniformLocation(programShader, "modelView");
		projectionViewLocation = glGetUniformLocation(programShader, "projectionView");
		colorLocation = glGetUniformLocation(programShader, "Color");

		positionAttribute = glGetAttribLocation(programShader, "Position");
		pointSizeLocation = glGetUniformLocation(programShader, "pointSize");

		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

		setUpPositionAttribute();
	}

	void Point2D::render(Mat4f projectionViewMatrix)
	{
		glUseProgram(programShader);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(position), &position, GL_DYNAMIC_DRAW);

		glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelView);
		glUniformMatrix4fv(projectionViewLocation, 1, GL_FALSE, projectionViewMatrix);
		glUniform4f(colorLocation, color->Red, color->Green, color->Blue, color->Alpha);

		glUniform1fv(pointSizeLocation, 1, &pointSize);

		setUpPositionAttribute();

		glDrawArrays(GL_POINTS, 0, 1);
	}

	Point2D::Point2D()
	{
		;
	}
	Point2D::Point2D(OpenML::Point2Df point)
	{
		setPosition(Vec2f{ point.x, point.y });
	}
}