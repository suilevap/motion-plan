// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Interface.h>
#include <FileStruct.h>

int _tmain(int argc, _TCHAR* argv[])
{

	//FileStruct f("map2.txt");

	//char * result = Action(f.GetBuffer());
	//printf(result);
	for (int i=0; i < 10000; i++)
	{
		TestGmInterface();
		if (i%100 == 0)
		{
			printf("%3d\n",i);
		}
	}
	getchar();	
	return 0;
}

