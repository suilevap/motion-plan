#pragma once
#ifndef _PathFinder_h_
#define _PathFinder_h_

#include <vector>
//#include <tuple>
#include "Map.h"
#include "PathPoint.h"
#include "Point.h"
#include "Path.h"
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
	CellQueue* _queue;
	//void DirToXY(int dir, int* x, int* y);
	//int XYToDir(int x, int y);
	//float ComputeCost(int x0, int y0, int x1, int y1);
	//float GetParentDist(int x, int y);
	bool CheckNeighbor(int index, int dx, int dy);
	float GetDistance(int index, int dx, int dy);
	float GetEstimateDistance(int index);
	Path* ExtractPath();
	void Step(int index);

public:
	PathFinder(Map<int>* map);
	~PathFinder();

	Path* Find(int x, int y, int goalX, int goalY);
	
	//only for debug purpose
	Map<float>* GetMapDist(){ return _mapDist;}
};

#endif //_PathFinder_h_