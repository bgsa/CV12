#pragma once

#include <fstream>
#include "Image.h"

typedef struct
{
	WORD SOIMarker;         // start of image marker
	WORD APP0_Marker;       // Application use marker
	WORD APP0_Length;       // Length of APP0 field
	BYTE Identifier[5];     // zero terminating string "JFIF",X'4A', X'46', X'49', X'46', X'00'
	BYTE Version[2];        // X'01',X'02'
	BYTE Units;             // units = 0:no units ;; units = 1:X and Y are dots per inch ;; units = 2:X and Y are dots per cm
	WORD XDensity;          // horizontal pixel density
	WORD YDensity;          // vertical pixel density
	BYTE XThumbnail;        // Thumbnail horizontal pixel density
	BYTE YThumbnail;        // Thumbnail vertical pixel density
} JFIFHeader;


class ImageJPEG : public Image
{
private:

public:	
	ColorRGBc getPixelRGB(int x, int y);
	
	static ImageJPEG * load(const char * filename)
	{
		ImageJPEG *image = new ImageJPEG;
		FILE *file = fopen(filename, "rb");

		JFIFHeader fileHeader;
		fread(&fileHeader, sizeof(JFIFHeader), 1, file);

		fclose(file);
		delete image;

		//NOT IMPLEMENTED EXCEPTION		

		return nullptr;
	}

};
