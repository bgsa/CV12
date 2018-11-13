#pragma once

#include <cstdlib>
#include "GlobalHeader.h"

class Shader
{
public:
	Shader();
	~Shader();

	static GLuint loadShaderProgram(const char * vertexShaderSource, const char * fragmentShaderSource) {
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;
		GLint linked;

		// Load the vertex/fragment shaders
		vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

		// Create the program object
		shaderProgram = glCreateProgram();

		if (shaderProgram == 0)
			return 0; //error

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		// Link the program
		glLinkProgram(shaderProgram);

		// Check the link status
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);

		if (!linked)
		{
			GLint infoLen = 0;

			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char *infoLog = (char*)malloc(sizeof(char) * infoLen);

				glGetProgramInfoLog(shaderProgram, infoLen, nullptr, infoLog);

				Log::error(string(infoLog));

				free(infoLog);
			}

			glDeleteProgram(shaderProgram);

			return 0;
		}

		glDetachShader(shaderProgram, vertexShader);
		glDetachShader(shaderProgram, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		
		return shaderProgram;
	}
	
	static GLuint loadShader(GLenum type, const char * source)
	{
		GLuint shader;
		GLint compiled;

		// Create the shader object
		shader = glCreateShader(type);

		if (shader == 0)
		{
			return 0;
		}

		// Load the shader source
		glShaderSource(shader, 1, &source, nullptr);

		// Compile the shader
		glCompileShader(shader);

		// Check the compile status
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char *infoLog = (char*)malloc(sizeof(char) * infoLen);

				glGetShaderInfoLog(shader, infoLen, nullptr, infoLog);

				Log::error(string(infoLog));
				Log::error("Shader Source: ");
				Log::error(string(source));

				free(infoLog);
			}

			glDeleteShader(shader);

			return 0;
		}

		return shader;
	}

};

