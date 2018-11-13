#pragma once

#include <cstdlib>
#include <vector>
#include "GlobalHeader.h"

#include <OpenML/Point2D.h>
#include "Log.h"
#include "Shader.h"
#include "Panel.h"
#include "ColorRGBA.h"

#include "Factory.h"
#include "IFileManager.h"
#include "Image.h"
#include "ImageFactory.h"

#include "GraphicObject2D.h"

#include "RendererSettings.h"

class Panel : public GraphicObject2D
{
private:	
	
	struct PanelShaderAttributes {
		GLfloat position[8];
		GLfloat texture[8];
	};

	PanelShaderAttributes panelAttributes = PanelShaderAttributes
	{
		{ //position  (space coordinates)
			0.0f, 0.0f, //bottom-left
			0.0f, 1.0f, //top-left
			1.0f, 0.0f, //bottom-right
			1.0f, 1.0f, //top-right	
		},
		{ //texture (u,v)
			0.0f, 0.0f,  // Top-left
			0.0f, 1.0f,  // Bottom-left
			1.0f, 0.0f,  // Top-right
			1.0f, 1.0f   // Bottom-right
		}
	};
	
	GLint positionAttribute;
	GLint textureAttribute;
	GLuint texture;
	string backgroundImage;

	GLint useHomographyLocation;
	GLint inverseHomographyMatrixLocation;

	void initVBO();
	void setUpPositionAttribute();
	void setUpTextureAttribute();

	void setUpImage(string filename);

public:

	Mat3f homographyMatrix = Mat3f::identity();
	int useHomography = 0;
	
	void setBackgroundImage(string filename);

	bool hasBackgroundImage();

	void setTextureCoordinates(GLfloat* textureCoord)
	{
		for (size_t i = 0; i < 8; i++)
			panelAttributes.texture[i] = textureCoord[i];
	}

	void setPositionAttributes(GLfloat* position)
	{
		for (size_t i = 0; i < 8; i++)
			panelAttributes.position[i] = position[i];
	}

	void setAttributes(GLfloat* position, GLfloat* textureCoord) 
	{
		for (size_t i = 0; i < 8; i++) 
		{
			panelAttributes.position[i] = position[i];
			panelAttributes.texture[i] = textureCoord[i];
		}
	}

	void init();

	void render(Mat4f projectionViewMatrix);

	virtual string toString() {
		return "Panel 2D";
	}

	~Panel();
};
