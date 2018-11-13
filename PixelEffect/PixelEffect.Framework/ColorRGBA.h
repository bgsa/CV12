#pragma once

#include "GlobalHeader.h"

template<typename T>
class ColorRGBA
{
public:
	T Red;
	T Green;
	T Blue;
	T Alpha;
	
	API_INTERFACE ColorRGBA(T red, T green, T blue, T alpha) 
	{
		Red = red;
		Green = green;
		Blue = blue;
		Alpha = alpha;
	}

	API_INTERFACE ColorRGBA<float> normalizeColor() 
	{
		return ColorRGBA<float>(
			Red / 255.0f,
			Green / 255.0f,
			Blue / 255.0f,
			Alpha / 255.0f);
	}

	/// <summary>
	/// Get a index from the vector
	/// </summary>
	API_INTERFACE Vec4<T> toVec4()
	{
		return Vec4<T>{ Red, Green, Blue, Alpha };
	}

	/// <summary>
	/// Get a index component color from the color
	/// </summary>
	API_INTERFACE T& operator[](int index)
	{
		assert(index >= 0 && index < 4);

		return toVec4()[index];
	}

	/// <summary>
	/// Implicit Convertion to array
	/// </summary>
	API_INTERFACE operator T* ()
	{
		return new T[4]{ Red, Green, Blue, Alpha };
	}

};

typedef ColorRGBA<float> ColorRGBAf;
typedef ColorRGBA<unsigned char> ColorRGBAc;