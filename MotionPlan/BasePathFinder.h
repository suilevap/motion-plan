#pragma once

#ifndef MOTIONPLAN_ASTAR_BASEPATHFINDER_H
#define MOTIONPLAN_ASTAR_BASEPATHFINDER_H

#include "MapView.h"
#include <vector>
#include "PathNode.h"
#include "CellQueue.h"
#include "EdgeInfo.h"
#include "Path.h"


namespace AStar
{

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
class BasePathFinder
{
public:
	typedef int NodeInfo;
	//typedef float CostInfo;
	//typedef Point PointInfo;
	//typedef Edge<NodeInfo,CostInfo> GridMapView::Edge;

private:	
	MapView<PointInfo, CellType, NodeInfo, CostInfo>* _map;
	std::vector<float> _mapCost;
	std::vector<NodeInfo> _mapParent;
	std::vector<EdgeInfo<NodeInfo,CostInfo>> _neighbors;
	
	PointInfo _goalPoint;
	PointInfo _startPoint;
	NodeInfo _goal;
	NodeInfo _start;
	CellQueue<NodeInfo, CostInfo>* _queue;
	//void DirToXY(int dir, int* x, int* y);
	//int XYToDir(int x, int y);
	//float ComputeCost(int x0, int y0, int x1, int y1);
	//float GetParentDist(int x, int y);
	bool CheckNeighbor(NodeInfo& node, EdgeInfo<NodeInfo, CostInfo>& edge);
	CostInfo GetDistance(NodeInfo& node, EdgeInfo<NodeInfo, CostInfo>& edge);
	CostInfo GetEstimateDistance(NodeInfo& node);
	Path<PointInfo>* ExtractPath();
	void Step(NodeInfo index);	

public:
	BasePathFinder(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map);
	~BasePathFinder();

	Path<PointInfo>* Find(PointInfo start, PointInfo goal);
	
	////only for debug purpose
	//std::vector<float>* GetMapDist(){ return _mapDist;};
};

#include "BasePathFinder.inl"

}

#endif //MOTIONPLAN_ASTAR_BASEPATHFINDER_H
