#define DllExport   __declspec( dllexport ) 

DllExport int CreateMap(int width, int height, float cellSize);
DllExport int SetCellMap(int mapIndex, int x, int y, int cell);
DllExport int GetCellMap(int mapIndex, int x, int y);
DllExport int DestroyMap(int mapIndex);

DllExport int CreatePathFinders(int mapIndex);
DllExport int FindPath(int pathFinderIndex, int x, int y, int goalX, int goalY);
DllExport int DestroyPathFinders(int pathFinderIndex);

DllExport int GetXPath(int pathIndex, int n);
DllExport int GetYPath(int pathIndex, int n);
DllExport int GetNPath(int pathIndex);
DllExport int DestroyPath(int pathIndex);



//extern "C"
//{

	//class Interface
	//{

	//public:
		//static 
			DllExport char* Action(char * map);

	//};

//}
