#pragma once

#ifndef MOTIONPLAN_ASTAR_BASEPATHFINDER_H
#define MOTIONPLAN_ASTAR_BASEPATHFINDER_H

#include "MapView.h"
#include <vector>
#include "PathNode.h"
#include "CellQueueRanked.h"
#include "EdgeInfo.h"
#include "Path.h"
#include "NodeState.h"
#include "PathFinder.h"


namespace AStar
{

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue = CellQueueRanked<int, CostInfo>> 
class BasePathFinder : public PathFinder<PointInfo, CellType, int, CostInfo>
{
public:
	typedef int NodeInfo;

protected:	
	//MapView<PointInfo, CellType, NodeInfo, CostInfo>* _map;

	std::vector<NodeState<NodeInfo,CostInfo>> _mapCost;

	std::vector<EdgeInfo<NodeInfo,CostInfo>> _neighbors;
	
	PointInfo _goalPoint;
	PointInfo _startPoint;

	CellQueue* _queue;

	bool CheckNeighbor(NodeInfo& node, EdgeInfo<NodeInfo, CostInfo>& edge, NodeInfo& goal);
	CostInfo GetDistance(NodeInfo& node, EdgeInfo<NodeInfo, CostInfo>& edge);
	CostInfo GetEstimateDistance(NodeInfo& node1, NodeInfo& node2);
	Path<PointInfo>* ExtractPath(NodeInfo& toPoint);
	void Step(NodeInfo& index, NodeInfo& goal);	

	virtual bool IsGoal(NodeInfo& goal);
public:
	BasePathFinder(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map);
	~BasePathFinder();

	//Path<PointInfo>* Find(PointInfo start, PointInfo goal);

	virtual void Init(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map);
	virtual void FindStart(NodeInfo start, NodeInfo goal);
	virtual NodeInfo FindStep();
	virtual bool FindIsPathExists(NodeInfo& node) ;
	virtual Path<PointInfo>* FindEnd(NodeInfo& curNode);
	
	////only for debug purpose
	//std::vector<float>* GetMapDist(){ return _mapDist;};
	virtual void ToOutputCurrentState();
};

#include "BasePathFinder.inl"

}

#endif //MOTIONPLAN_ASTAR_BASEPATHFINDER_H
