#pragma once

#include "StringHelper.h"
#include "Image.h"
#include "ImagePNG.h"
#include "ImageBMP.h"
#include "ImageJPEG.h"

class ImageFactory 
{
public:

    static Image * load(const char * filename) 
	{
		Image *image = nullptr;

		if (StringHelper::endWith(filename, ".png"))
			image = (Image*)ImagePNG::load(filename);
		else
		if (StringHelper::endWith(filename, ".bmp")) 
			image = (Image*) ImageBMP::load(filename);
		else 
		if (StringHelper::endWith(filename, ".jpg"))
			image = (Image*)ImageJPEG::load(filename);

		return image;
	}

};
