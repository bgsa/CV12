#pragma once

#include "GlobalHeader.h"

template<typename T>
class ColorRGB
{
public:
	T Red;
	T Green;
	T Blue;

	API_INTERFACE ColorRGB(T red, T green, T blue)
	{
		Red = red;
		Green = green;
		Blue = blue;
	}

	API_INTERFACE ColorRGB<float> normalizeColor()
	{
		return ColorRGB<float>(
			Red / 255.0f,
			Green / 255.0f,
			Blue / 255.0f);
	}
};

typedef ColorRGB<float> ColorRGBf;
typedef ColorRGB<unsigned char> ColorRGBc;