#pragma once

#include "GlobalHeader.h"
#include <cstdio>
#include <iostream>
#include <string>

#ifdef ANDROID
#include <android/log.h>
#endif

using namespace std;

class Log
{
public:

	static void error(string errorMessage)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_ERROR, "ERROR", "%s", errorMessage.c_str());
#endif
#ifdef  WINDOWS
		printf("%s%c", errorMessage.c_str(), END_OF_LINE);
#endif
	}

	static void info(string message)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_INFO, "INFO", "%s", message.c_str());
#endif
#ifdef  WINDOWS
		printf("%s%c", message.c_str(), END_OF_LINE);
#endif		
	}

	static void debug(string message)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "%s", message.c_str());
#endif
#ifdef  WINDOWS
		printf("%s%c", message.c_str(), END_OF_LINE);
#endif		
	}

	static void glErrors(const char *file, int line)
	{
		GLenum error = glGetError();
		string msg;

		while (error != GL_NO_ERROR) {
			string errorMessage = "";

			switch (error)
			{
			case GL_INVALID_OPERATION:
				errorMessage = "INVALID_OPERATION";
				break;

			case GL_INVALID_ENUM:
				errorMessage = "INVALID_ENUM";
				break;

			case GL_INVALID_VALUE:
				errorMessage = "INVALID_VALUE";
				break;

			case GL_OUT_OF_MEMORY:
				errorMessage = "OUT_OF_MEMORY";
				break;

			case GL_INVALID_FRAMEBUFFER_OPERATION:
				errorMessage = "INVALID_FRAMEBUFFER_OPERATION";
				break;
			}
			
			//char * lineAsString = (char *) &line;
			//msg = "GL_" + errorMessage + " - " + file + ":" + to_string(line) + END_OF_LINE;
			//Log::error(msg.c_str());
			Log::error(errorMessage);

			error = glGetError();
		}
	}

	static void onError(int errorCode, const char* description)
	{
		error("Error: " + string(description));
	}

};
