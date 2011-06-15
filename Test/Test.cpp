// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Interface.h>
#include <FileStruct.h>

int _tmain(int argc, _TCHAR* argv[])
{
	char * result = Action();
	printf(result);
	return 0;
}

