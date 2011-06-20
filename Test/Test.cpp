// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Interface.h>
#include <FileStruct.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//FileStruct f("\\maps\\map0.txt");
	//FileStruct f2(".\\maps\\map0.txt");
	//FileStruct f3(".\\map0.txt");
	//FileStruct f4("map0.txt");
	//FileStruct f5("e:\\code\\aigamedev\\motion-plan\\Debug\\maps\\map0.txt");

	FileStruct f("map1.txt");

	char * result = Action(f.GetBuffer());
	printf(result);
	return 0;
}

