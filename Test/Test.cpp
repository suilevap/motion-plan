// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>

#include <Interface.h>
#include <FileStruct.h>

int _tmain(int argc, _TCHAR* argv[])
{
	TestSparsePerformance(true);

	clock_t time0, time1, times;
	//FileStruct f("map2.txt");

	//char * result = Action(f.GetBuffer());
	//printf(result);
	//TestPerformance(true);
	TestSparsePerformance(true);
	times = clock();
	time0 = times;
	for (int i=1; i < 100000; i++)
	{
		//TestPerformance(false);
		TestSparsePerformance(false);
		if (i%1000 == 0)
		{
			time1 = clock();
			printf("%3dk time: %4d, avg time: %4d\n",i/1000, (time1 - time0), (time1 - times)/(i/1000) );
			time0 = time1;
		}
	}
	getchar();	
	return 0;
}

