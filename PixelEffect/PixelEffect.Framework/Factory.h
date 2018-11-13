#pragma once

#include "IFileManager.h"
#include "Log.h"

#ifdef ANDROID
#include "FileManagerAndroid.h"
#endif
#ifdef WINDOWS
#include "FileManagerWindows.h"
#endif

class Factory
{
public:

	static IFileManager * getFileManagerInstance() 
	{
#ifdef ANDROID
		return new FileManagerAndroid;
#endif
#ifdef WINDOWS
		return new FileManagerWindows;
#endif
	}

};

