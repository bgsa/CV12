#pragma once

#include <stdlib.h>
#include <PNG/png.h>
#include "Log.h"
#include "Image.h"

#ifdef ANDROID
#include <android/asset_manager.h> 
#include "FileManagerAndroid.h"
#endif

class ImagePNG : public Image
{
private:

public:
	ColorRGBc getPixelRGB(int x, int y);

	static GLenum getGlColorFormat(const int pngColorFormat)
	{
		switch (pngColorFormat)
		{
		case PNG_COLOR_TYPE_GRAY:
			return GL_LUMINANCE;

		case PNG_COLOR_TYPE_RGB:
			return GL_RGB;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			return GL_RGBA;

		case PNG_COLOR_TYPE_GRAY_ALPHA:
			return GL_LUMINANCE_ALPHA;
		}

		return 0;
	}

#ifdef ANDROID
	static void png_asset_read(png_structp png_ptr, png_bytep data, png_size_t length)
	{
		AAsset* file = (AAsset*)png_get_io_ptr(png_ptr);
		AAsset_read(file, data, length);
	}
#endif

	static void closeFile(void * file)
	{
#if defined(WINDOWS) || defined(LINUX) || defined(MAC) || defined(UNIX)
		fclose((FILE *)file);
#endif
#ifdef ANDROID
		AAsset_close((AAsset *)file);
#endif
	}

	static ImagePNG * load(const char * filename)
	{
		png_byte header[8];
		png_uint_32 width, height;
		int bit_depth, color_type;

#ifdef ANDROID
		FileManagerAndroid fileManager;
		AAssetManager *assetManager = fileManager.getAssetManager();
		AAsset* file = AAssetManager_open(assetManager, filename, AASSET_MODE_STREAMING);

		//read the header
		AAsset_read(file, header, 8);
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(MAC) || defined(UNIX)
		FILE *file = fopen(filename, "rb");
		fread(header, 1, 8, file);
#endif

		//create png struct
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
		{
			Log::error("error: png_create_read_struct returned 0.");
			closeFile(file);
			return 0;
		}

		// create png info struct
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
		{
			Log::error("error: png_create_info_struct returned 0.");
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			closeFile(file);
			return 0;
		}

		// create png info struct
		png_infop end_info = png_create_info_struct(png_ptr);
		if (!end_info)
		{
			Log::error("error: png_create_info_struct returned 0.");
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			closeFile(file);
			return 0;
		}

		/* this code have a problem with libpng version -
		//the first IF works on libpng16 and
		the second IF SHOULD work on libpng12
				// the code in this if statement gets called if libpng encounters an error
				//if (setjmp(png_jmpbuf(png_ptr)))
				//if (setjmp(png_ptr->jmpbuf))  // Warning is unavoidable if #define PNG_DEPSTRUCT is not present
				{
					Log::error("error from libpng");
					png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
					closeFile(file);
					return 0;
				}
		*/

#ifdef ANDROID
		png_set_read_fn(png_ptr, file, png_asset_read);
#else
		png_init_io(png_ptr, file);
#endif				

		//let libpng know you already read the first 8 bytes
		png_set_sig_bytes(png_ptr, 8);
		
		// read all the info up to the image data
		png_read_info(png_ptr, info_ptr);
		
		// get info about png
		png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

		// Update the png info struct.
		png_read_update_info(png_ptr, info_ptr);

		// Row size in bytes.
		size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr); //android
		
		// Allocate the image_data as a big block, to be given to opengl
		png_byte * data = (png_byte *)malloc(rowbytes * height * sizeof(png_byte) + 15);
		if (data == NULL)
		{
			fprintf(stderr, "error: could not allocate memory for PNG image data\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			closeFile(file);
			return 0;
		}

		// row_pointers is for pointing to image_data for reading the png with libpng
		png_bytep * row_pointers = (png_bytep *)malloc(height * sizeof(png_bytep));
		if (row_pointers == NULL)
		{
			fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			free(data);
			closeFile(file);
			return 0;
		}
		
		// set the individual row_pointers to point at the correct offsets of image_data
		for (unsigned int i = 0; i < height; i++)
			row_pointers[height - 1 - i] = data + i * rowbytes;

		// read the png into image_data through row_pointers
		png_read_image(png_ptr, row_pointers);

		// clean up
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(row_pointers);
		
		closeFile(file);
		
		ImagePNG *image = new ImagePNG;
		image->width = width;
		image->height = height;
		image->data = data;
		image->colorFormat = getGlColorFormat(color_type);
		
		return image;
	}

};
