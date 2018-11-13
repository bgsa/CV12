#pragma once

#include "GlobalHeader.h"
#include "IFile.h"

using namespace std;

class IFileManager
{
public:
	virtual ~IFileManager() {};

	virtual vector<string> getFilesFromResource() = 0;

	virtual vector<string> getFilesFromFolder(string folder, string suffix = "") = 0;

	virtual string readTextFile(const char * filename) = 0;

	virtual char* readBinaryFile(const char * filename, size_t& size) = 0;

	virtual bool exists(const char * filename) = 0;

	virtual IFile* open(string filename) = 0;
};