#pragma once

#include "GlobalHeader.h"
#include <fstream>
#include "Image.h"

#ifdef ANDROID
#include <android/asset_manager.h> 
#include "FileManagerAndroid.h"
#endif

#pragma pack(push, 2)
typedef struct
{
	char type[2];
	unsigned int   size;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int   offBits;
} BMPFileHeader;
typedef struct
{
	unsigned int   size;            /* Size of info header */
	int            width;           /* Width of image */
	int            height;          /* Height of image */
	unsigned short planes;          /* Number of color planes */
	unsigned short bitCount;        /* Number of bits per pixel */
	unsigned int   compression;     /* Type of compression to use (0=none, 1=RLE-8, 2=RLE-4) */
	unsigned int   sizeImage;       /* Size of image data (including padding) */
	int            xPelsPerMeter;   /* X pixels per meter - horizontal resolution in pixels per meter (unreliable) */
	int            yPelsPerMeter;   /* Y pixels per meter - vertical resolution in pixels per meter (unreliable) */
	unsigned int   colorsUsed;      /* Number of colors used */
	unsigned int   colorsImportant; /* Number of important colors */
} BMPHeaderInfo;
#pragma pack(pop)

class ImageBMP : public Image
{
private:

public:
	
	ColorRGBc getPixelRGB(int x, int y);
	
	static ImageBMP * load(const char * filename)
	{
		ImageBMP *image = new ImageBMP;
		image->colorFormat = GL_RGB;

		BMPFileHeader fileHeader;
		BMPHeaderInfo headerInfo;
				
#ifdef ANDROID
		FileManagerAndroid fileManager;
		AAssetManager *assetManager = fileManager.getAssetManager();
		AAsset* file = AAssetManager_open(assetManager, filename, AASSET_MODE_RANDOM);

		AAsset_read(file, &fileHeader, sizeof(BMPFileHeader));
		AAsset_read(file, &headerInfo, sizeof(BMPHeaderInfo));
		
		image->width = headerInfo.width;
		image->height = headerInfo.height;

		unsigned int size = 3 * image->width * image->height;
		image->data = new unsigned char[size]; // allocate 3 bytes per pixel
		AAsset_read(file, image->data, size);

		AAsset_close(file);
#endif
#ifdef WINDOWS
		FILE *file = fopen(filename, "rb");
		
		fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
		fread(&headerInfo, sizeof(BMPHeaderInfo), 1, file);

		image->width = headerInfo.width;
		image->height = headerInfo.height;

		fseek(file, 54 * sizeof(char), SEEK_SET); //move o cursor para a posição 54 do arquivo, contando do início
		
		unsigned int size = 3 * image->width * image->height;
		image->data = new unsigned char[size]; // allocate 3 bytes per pixel
		fread(image->data, sizeof(unsigned char), size, file); // read the rest of the data at once

		fclose(file);
#endif
		//coloca no formato RGB ao invés de BGR
		/*		
		for (int i = 0; i < size; i += 3)		
		{
			unsigned char tmp = image->data[i];
			image->data[i] = image->data[i + 2];
			image->data[i + 2] = tmp;
		}
		*/

		/*
		int padding = 0;
		int scanlinebytes = image->width * 3;
		while ((scanlinebytes + padding) % 4 != 0)
			padding++;
		int psw = scanlinebytes + padding;
		
		long bufpos = 0;
		long newpos = 0;
		for (int y = 0; y < image->height; y++)
			for (int x = 0; x < 3 * image->width; x += 3)
			{
				newpos = y * 3 * image->width + x;
				bufpos = (image->height - y - 1) * psw + x;

				image->data[newpos] = image->data[bufpos + 2];
				image->data[newpos + 1] = image->data[bufpos + 1];
				image->data[newpos + 2] = image->data[bufpos];
			}
			*/

		return image;
	}

};
