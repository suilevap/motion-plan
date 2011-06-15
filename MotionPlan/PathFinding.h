#pragma once
#include <vector>
//#include <tuple>
#include "Map.h"
#include "PathPoint.h"
#include "Point.h"

using namespace std;
//using namespace std::tr1;

typedef priority_queue<PathPoint,vector<PathPoint>,less<vector<PathPoint>::value_type>> cellQueue;

class PathFinding
{
private:
	Map<int>* _map;
	Map<float>* _mapDist;
	Map<int>* _mapParent;
	int _goalX;
	int _goalY;
	int _goal;
	int _start;
	//void DirToXY(int dir, int* x, int* y);
	//int XYToDir(int x, int y);
	//float ComputeCost(int x0, int y0, int x1, int y1);
	//float GetParentDist(int x, int y);
	bool CheckNeighbor(int index, int dx, int dy, cellQueue* queue);
	float GetStepDistance(int index, int dx, int dy);
	float GetEstimateDistance(int index);
	bool CheckCell(int index, float curDist);
	vector<Point> ExtractPath();
public:
	PathFinding(Map<int>* map);
	~PathFinding(void);

	vector<Point> Find(int x, int y, int goalX, int goalY);
};
