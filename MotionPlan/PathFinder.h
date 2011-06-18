#pragma once
#ifndef _PathFinder_h_
#define _PathFinder_h_

#include <vector>
//#include <tuple>
#include "Map.h"
#include "PathPoint.h"
#include "Point.h"
#include "CellQueue.h"

//using namespace std;
//using namespace std::tr1;

class PathFinder
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
	bool CheckNeighbor(int index, int dx, int dy, CellQueue* queue);
	float GetStepDistance(int index, int dx, int dy);
	float GetEstimateDistance(int index);
	bool CheckCell(int index, float curDist);
	std::vector<Point> ExtractPath();

public:
	PathFinder(Map<int>* map);
	~PathFinder();

	std::vector<Point> Find(int x, int y, int goalX, int goalY);
};

#endif //_PathFinder_h_