#pragma once

#ifndef MOTIONPLAN_ASTAR_BASEPATHFINDER_H
#define MOTIONPLAN_ASTAR_BASEPATHFINDER_H

#include "MapView.h"
#include <vector>
//#include "PathPoint.h"
//#include "Point.h"
//#include "Path.h"
//#include "CellQueue.h"
namespace Astar
{

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
class BasePathFinder
{
	typedef int NodeInfo;
	//typedef float CostInfo;
	//typedef Point PointInfo;
	//typedef Edge<NodeInfo,CostInfo> GridMapView::Edge;

private:	
	MapView<PointInfo, CellType, NodeInfo, CostInfo>* _map;
	std::vector<float> _mapDist;
	std::vector<NodeInfo> _mapParent;
	
	PointInfo _goalPoint;
	PointInfo _startPoint;
	NodeInfo _goal;
	NodeInfo _start;
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

	Path* Find(int x, int y, int goalX, int goalY, float estimateAlpha);
	
	//only for debug purpose
	Map<float>* GetMapDist(){ return _mapDist;};
};

#include "BasePathFinder.inl"

}

#endif //MOTIONPLAN_ASTAR_BASEPATHFINDER_H
