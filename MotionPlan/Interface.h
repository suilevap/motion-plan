#include "DllExport.h"

DllExport double InitGM();
DllExport double CloseGM();

DllExport double CreateMap(double width, double height, double cellSize);
DllExport double CreateHexMap(double width, double height, double cellSize);
DllExport double CreateSparseMap(double width, double height, double cellSize);
DllExport double CreateQuadMap(double gridMapIndex);
DllExport double CreateNavRectMap(double gridMapIndex);
DllExport double CreateMapFromSurface(double sufaceId, double scale);

DllExport double SetCellMap(double mapIndex, double x, double y, double cell);
DllExport double SetCellMapRegion(double mapIndex, double x, double y, double w, double h, double cell);
DllExport double GetCellMap(double mapIndex, double x, double y);
DllExport double DestroyMap(double mapIndex);
DllExport double DrawMap(double mapIndex);
DllExport double DrawNavRectMap(double mapIndex);
DllExport double DrawPathFinder(double pathFinderIndex);




DllExport double CreatePathFinder(double mapIndex);
double CreatePathFinderDebug(double mapIndex, double mapDebugIndex);
DllExport double FindPath(double pathFinderIndex, double x, double y, double goalX, double goalY);
DllExport double FindPathGM(double pathFinderIndex, double x, double y, double goalX, double goalY, double gmPath);
DllExport double DestroyPathFinder(double pathFinderIndex);

DllExport double GetXPath(double pathIndex, double n);
DllExport double GetYPath(double pathIndex, double n);
DllExport double GetNPath(double pathIndex);
DllExport char* GetGmPath(double pathIndex);
DllExport double ConvertToGmPath(double pathIndex, double gmPathId);
DllExport double DestroyPath(double pathIndex);


DllExport double Test();

void OutputPath(double mapObstInd, double path);
