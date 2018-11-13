#pragma once

#include "GlobalHeader.h"
#include "ColorRGB.h"

class Image 
{
private:
	
protected:
	int width;
	int height;
	unsigned char* data;
	GLenum colorFormat;
	
public:
    Image();   
	virtual ~Image();
	
	int getWidth();
	int getHeight();	
	unsigned char * getData();
	GLenum getColorFormat();
	virtual ColorRGBc getPixelRGB(int x, int y) = 0;    
};
