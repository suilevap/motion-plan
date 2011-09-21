#include "StdAfx.h"

#include "FileStruct.h"
#include <iostream>
#include <stdio.h>


FileStruct::FileStruct(char* fileName)
{
	_buffer = NULL;
	_size = 0;
	Name = fileName;
	GetBuffer();
}

FileStruct::~FileStruct(void)
{
	if (_buffer != NULL)
	{
		free(_buffer);
	}

}


size_t FileStruct::LoadFile(char* path, char* &buffer)
{
	FILE *file;
	
	size_t fileLen;
	
	//Open file
	file = fopen(path, "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", path);
		return 0;
	}
	
	//Get file length
	fseek(file, 0, SEEK_END);
	fileLen = ftell(file);
	fseek(file, 0, SEEK_SET);

	//Allocate memory
	buffer=(char *)malloc(fileLen+1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
        fclose(file);
		return 0;
	}

	//Read file contents into buffer
	fread(buffer, fileLen, 1, file);
	buffer[fileLen] = 0;
	fclose(file);

	return fileLen;
}

char * FileStruct::GetBuffer()
{
	if (_buffer == NULL)
	{
		_size = this->LoadFile(Name, _buffer);
	}
	return _buffer;
}

size_t FileStruct::GetSize()
{
	if (_buffer == NULL)
	{
		_size = this->LoadFile(Name, _buffer);
	}
	return _size;
}
