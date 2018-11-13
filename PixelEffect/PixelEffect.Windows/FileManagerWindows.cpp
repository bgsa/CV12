#include "FileManagerWindows.h"

inline bool checkFile(ifstream& file, const char * filename) 
{
    if ( file.fail() || file.bad() || ! file.is_open() ) 
    {
		string str1 = strerror(errno);
		string str = ": ";
		string message = str1 + str + filename;
        
		Log::error(message);
        
        return false;
    }
    
    return true;
}

vector<string> FileManagerWindows::getFilesFromResource()
{
	vector<string> files;
	files.push_back("teste.txt");
	return files;
}


vector<string> FileManagerWindows::getFilesFromFolder(string folder, string suffix)
{
	vector<string> files;
#if defined(WINDOWS)
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(search_path.c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			bool isDirectory = fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
			
			if ( ! isDirectory )
			{
				string filename = fd.cFileName;

				if (suffix.empty())
					files.push_back(filename);
				else
					if (StringHelper::endWith(filename.c_str(), suffix.c_str()))
						files.push_back(filename);
			}
		} while (FindNextFile(hFind, &fd));

		FindClose(hFind);
	}
#endif
	return files;
}

bool FileManagerWindows::exists(const char * filename)
{
    ifstream file(filename);
    return file.good();
}

string FileManagerWindows::readTextFile(const char * filename)
{
	ifstream file(filename);

	file.seekg(0, ios::end);

	size_t size = (size_t) file.tellg();

	string content(size, ' ');

	file.seekg(0);
	file.read(&content[0], size);

	return content;
}

char* FileManagerWindows::readBinaryFile(const char * filename, size_t& size)
{
	ifstream file(filename, ios::binary | ios::ate);
	size = (size_t) file.tellg();
	file.seekg(0, ios::beg);

	char* content = (char*) malloc(size);

	file.read(content, size);

	return content;
}

IFile* FileManagerWindows::open(string filename)
{
	FileWindows* file = new FileWindows(filename);
	return file;
}