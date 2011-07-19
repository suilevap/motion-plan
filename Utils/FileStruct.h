#pragma once

class FileStruct
{
private:
	char * _buffer;

	size_t _size;

	size_t LoadFile(char * path, char * & buffer);

public:
	char * Name;

	size_t GetSize();
	char * GetBuffer();

	FileStruct(char * fileName);
	~FileStruct(void);
};
