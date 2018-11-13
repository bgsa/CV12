#pragma once

#include "GlobalHeader.h"
#include <iomanip>

template <typename T>
class Mat
{
protected:

	static string toString(T * data, int size, int precision = 4)
	{
		string content;
		size_t total = (int)(size * size);

		for (size_t i = 0; i < total; i++)
		{
			stringstream stream;
			stream << fixed << setprecision(precision) << data[i];
			string numberAsString = stream.str();

			bool isPositive = data[i] >= 0;

			if (isPositive)
				numberAsString = " " + numberAsString;

			content += " " + numberAsString + " ";

			if ((i + 1) % size == 0)
				content += '\n';
		}

		return content;
	}

};

