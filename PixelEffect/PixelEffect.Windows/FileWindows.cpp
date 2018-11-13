#include "FileWindows.h"

FileWindows::FileWindows(string filename)
{
	file = fopen(filename.c_str(), "rb");
}

void FileWindows::read(void* buffer, size_t size, size_t count)
{
	fread(buffer, size, count, file);
}

void FileWindows::seek(long offset)
{
	fseek(file, offset, SEEK_SET);
}

void FileWindows::close()
{
	fclose(file);
}

FileWindows::~FileWindows()
{
	if (file != NULL)
		fclose(file);
}
