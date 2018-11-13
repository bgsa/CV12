#pragma once

#include <vector>
#include <cstring>

#ifdef OPENGL

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#endif

#ifdef OPENGLES
#include <GLES3/gl3.h>
#endif

#include <OpenML/MathPP.h>
#include <OpenML/Vec3.h>
#include <OpenML/Mat3.h>
#include <OpenML/Mat4.h>

typedef unsigned char  BYTE;  // 1byte
typedef unsigned short WORD;  // 2bytes
typedef unsigned long  DWORD; // 4bytes

const float FRAMES_PER_SECOND = 30.0f;

extern "C" {
	const char END_OF_LINE = '\n';
}

#include "Log.h"
