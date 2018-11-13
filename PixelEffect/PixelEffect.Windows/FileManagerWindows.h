#pragma once

#include "GlobalHeader.h"

#if defined(WINDOWS)
#include <Windows.h>
#endif
#include <fstream>
#include <iostream>

#include "StringHelper.h"
#include "IFileManager.h"
#include "IFile.h"
#include "FileWindows.h"

using namespace std;

class FileManagerWindows : public IFileManager
{
public:
	vector<string> getFilesFromResource();

	vector<string> getFilesFromFolder(string folder, string suffix = "");

	string readTextFile(const char * filename);

	char* readBinaryFile(const char * filename, size_t& size);
    
    bool exists(const char * filename);    

	IFile* open(string filename);
};