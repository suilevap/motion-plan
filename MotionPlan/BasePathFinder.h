#pragma once

#ifndef MOTIONPLAN_ASTAR_BASEPATHFINDER_H
#define MOTIONPLAN_ASTAR_BASEPATHFINDER_H

#include "MapView.h"
#include <vector>
#include "FastVector.h"
#include "Pool.h"

#include "PathNode.h"
#include "CellQueueRanked.h"
#include "CellQueueRankedV2.h"
#include "CellQueueSimple.h"

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
class BasePathFinder : public PathFinder<PointInfo, CellType, CostInfo>
{
public:
	typedef int NodeInfo;

protected:	
    static const int StartNodeIndex = 0;
	//MapView<PointInfo, CellType, NodeInfo, CostInfo>* _map;

	std::vector<NodeState<NodeInfo,CostInfo>> _mapCost;

	FastVector<EdgeInfo<NodeInfo,CostInfo>> _neighbors;
	
	PointInfo _goalPoint;
	PointInfo _startPoint;

	CellQueue* _queue;
    Pool<PathNode<NodeInfo, CostInfo>> _pathNodePool;
    
    PathNode<NodeInfo, CostInfo> _goalState;

    void ProcessNeighboors(int parentNode);
	bool CheckNeighbor(NodeInfo node, EdgeInfo<NodeInfo, CostInfo>& edge);
	CostInfo GetDistance(NodeInfo node, EdgeInfo<NodeInfo, CostInfo>& edge);
	CostInfo GetEstimateDistance(NodeInfo node1);
	Path<PointInfo>* ExtractPath(PointInfo toPoint);
	void Step(NodeInfo node);	

	virtual bool IsGoal(NodeInfo goal);
    int GetNearestNode(PointInfo toPoint);
public:

	BasePathFinder(MapView<PointInfo, CellType, CostInfo>* map);
	virtual ~BasePathFinder();

	//Path<PointInfo>* Find(PointInfo start, PointInfo goal);

	virtual void Init(MapView<PointInfo, CellType, CostInfo>* map);
	virtual void FindStart(PointInfo start, PointInfo goal);
	virtual NodeInfo FindStep();
	virtual bool FindIsPathExists(NodeInfo node) ;
	virtual Path<PointInfo>* FindEnd(PointInfo curNode);
	
	////only for debug purpose
	//std::vector<float>* GetMapDist(){ return _mapDist;};
	virtual void ToOutputCurrentState();
};

#include "BasePathFinder.inl"

}

#endif //MOTIONPLAN_ASTAR_BASEPATHFINDER_H
