#pragma once

#ifndef MOTIONPLAN_ASTAR_BASEPATHFINDER_H
#define MOTIONPLAN_ASTAR_BASEPATHFINDER_H

#include "MapView.h"
#include <vector>
#include "PathNode.h"
#include "CellQueue.h"
#include "EdgeInfo.h"
#include "Path.h"
#include "NodeState.h"


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


private:	
	MapView<PointInfo, CellType, NodeInfo, CostInfo>* _map;
	std::vector<NodeState<NodeInfo,CostInfo>> _mapCost;

	std::vector<EdgeInfo<NodeInfo,CostInfo>> _neighbors;
	
	PointInfo _goalPoint;
	PointInfo _startPoint;
	NodeInfo _goal;
	NodeInfo _start;
	CellQueue<NodeInfo, CostInfo>* _queue;

	//for debug
	MapView<PointInfo, CellType, NodeInfo, CostInfo>* _mapForStateDebug;

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
	void InitDebug(MapView<PointInfo, CellType, NodeInfo, CostInfo>* mapForStateDebug) { _mapForStateDebug = mapForStateDebug; }
	void ToOutputCurrentState();
};

#include "BasePathFinder.inl"

}

#endif //MOTIONPLAN_ASTAR_BASEPATHFINDER_H
