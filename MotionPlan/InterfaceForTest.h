#include "DllExport.h"

DllExport void TestGmInterface();
DllExport void TestPerformance(bool outputMap);
DllExport void TestHexPerformance(bool outputMap);
DllExport void TestSparsePerformance(bool outputMap);

DllExport char* Action(char * map);

DllExport double GenMap(int w, int h, int cellSize);
DllExport double GenPathFinder(double map, int w, int h, int cellSize);
DllExport void FindPathTest(double map, double pathFinder, int w, int h, int cellSize, bool outputMap);
