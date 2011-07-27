#define DllExport extern "C" __declspec( dllexport )

DllExport double InitGM();
DllExport double CloseGM();

DllExport double CreateMap(double width, double height, double cellSize);
DllExport double SetCellMap(double mapIndex, double x, double y, double cell);
DllExport double SetCellMapRegion(double mapIndex, double x, double y, double w, double h, double cell);
DllExport double GetCellMap(double mapIndex, double x, double y);
DllExport double DestroyMap(double mapIndex);

DllExport double CreatePathFinder(double mapIndex);
DllExport double FindPath(double pathFinderIndex, double x, double y, double goalX, double goalY);
DllExport double DestroyPathFinder(double pathFinderIndex);

DllExport double GetXPath(double pathIndex, double n);
DllExport double GetYPath(double pathIndex, double n);
DllExport double GetNPath(double pathIndex);
DllExport char* GetGmPath(double pathIndex);
DllExport double ConvertToGmPath(double pathIndex, double gmPathId);
DllExport double DestroyPath(double pathIndex);

DllExport void TestGmInterface();
DllExport void TestPerformance(bool outputMap);

DllExport double Test();

//extern "C"
//{

	//class doubleerface
	//{

	//public:
		//static 
			//DllExport char* Action(char * map);

	//};

//}
