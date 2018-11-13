#pragma once

#include "GlobalHeader.h"

using namespace std;

class GLConfig 
{
private:

public:

	static float getGLfloat(GLenum param)
	{
		GLfloat value;
		glGetFloatv(param, &value);

		return value;
	}

	static string getGLString(GLenum param)
	{
		const unsigned char * value = glGetString(param);
		string result = reinterpret_cast<const char*>(value);

		return result;
	}

	static string getGLVendor() 
	{
		return getGLString(GL_VENDOR);
	}

	static string getGLRenderer()
	{
		return getGLString(GL_RENDERER);
	}

	static string getGLVersion()
	{
		return getGLString(GL_VERSION);
	}

	static string getGLShadingLanguageVersion()
	{
		return getGLString(GL_SHADING_LANGUAGE_VERSION);
	}

	static vector<string> getGLExtensions() 
	{
		vector<string> extensions;

		GLint extensionsCount = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &extensionsCount);

		for (GLint i = 0; i < extensionsCount; i++)
		{
			const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
			extensions.push_back(extension);
		}

		return extensions;
	}

	static int getMaximmumVertexAttribute() 
	{
		int maxAttributeSupported;		

		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributeSupported);

		return maxAttributeSupported;
	}
	
#ifdef __OPENGL__
	static void setGLFogFastMode() 
	{
		glHint(GL_FOG_HINT, GL_FASTEST);
	}
	static void setGLFogNiceMode()
	{
		glHint(GL_FOG_HINT, GL_NICEST);
	}

	static void setGLLineSmoothFastMode()
	{
		glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	}
	static void setGLLineSmoothNiceMode()
	{
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	}

	static void setGLPerspectiveCorretionFastMode()
	{
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	}
	static void setGLPerspectiveCorretionNiceMode()
	{
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}

	static void setGLPointSmoothFastMode()
	{
		glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	}
	static void setGLPointSmoothNiceMode()
	{
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	}

	static void setGLPolygonSmoothFastMode()
	{
		glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	}
	static void setGLPolygonSmoothNiceMode()
	{
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	}
#endif

};