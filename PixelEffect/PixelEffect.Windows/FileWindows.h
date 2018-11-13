#pragma once

#include <fstream>
#include "GlobalHeader.h"
#include "IFile.h"

using namespace std;

class FileWindows : public IFile
{
private:
	FILE *file;

public:
	FileWindows(string filename);

	void read(void* buffer, size_t size, size_t count = 1);
	void seek(long offset);
	void close();

	~FileWindows();
};

