#pragma once

#include "GlobalHeader.h"
#include <sstream>

using namespace std;

class StringHelper
{
public:

	static string toLowerCase(string value)
	{
		char* stringAsArray = (char*)value.c_str();

		for (size_t i = 0; i < value.length(); i++)
			stringAsArray[i] = tolower(stringAsArray[i]);

		return string(stringAsArray);
	}

	static string toUpperCase(string value) 
	{
		char* stringAsArray = (char*) value.c_str();

		for (size_t i = 0; i < value.length(); i++)
			stringAsArray[i] = toupper(stringAsArray[i]);

		return string(stringAsArray);
	}

	static bool startWith(string text, string value) 
	{
		size_t textLength = text.length();
		size_t valueLength = value.length();

		if (valueLength > textLength)
			return false;
				
		string startSubstring = text.substr(0, valueLength);
		
		return strcmp(startSubstring.c_str(), value.c_str()) == 0;
	}

	static bool endWith(const char * text, const char * suffix)
	{
		if (text == nullptr || suffix == nullptr)
			return false;

		size_t textLength = strlen(text);
		size_t suffixLength = strlen(suffix);

		if (suffixLength > textLength)
			return false;

		return strncmp(text + textLength - suffixLength, suffix, suffixLength) == 0;
	}

	template <typename T>
	static string toString(T value)
	{
		ostringstream os;
		os << value;
		return os.str();
	}

	static vector<string> split(string text, const char* separator) 
	{
		vector<string> result;
		char* values = strtok( (char*) text.c_str(), separator);

		while (values != NULL)
		{
			result.push_back(values);
			values = strtok(NULL, separator);
		}

		return result;
	}

};

