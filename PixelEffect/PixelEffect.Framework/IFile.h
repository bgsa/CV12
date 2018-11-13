#pragma once

class IFile 
{
public:

	//virtual void read(char* buffer, size_t size, size_t count = 1) = 0;
	virtual void read(void* buffer, size_t size, size_t count = 1) = 0;
	virtual void seek(long offset) = 0;
	virtual void close() = 0;
	
	virtual ~IFile() {};

};