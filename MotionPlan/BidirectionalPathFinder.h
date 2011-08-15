#pragma once

#ifndef MOTIONPLAN_ASTAR_BIDIRECTIONALPATHFINDER_H
#define MOTIONPLAN_ASTAR_BIDIRECTIONALPATHFINDER_H

#include "MapView.h"
#include <vector>
#include "PathNode.h"

#include "EdgeInfo.h"
#include "Path.h"
#include "NodeState.h"


namespace AStar
{

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
class BidirectionalPathFinder: public AStar::PathFinder<PointInfo, CellType, int, CostInfo>
{
public:
	typedef int NodeInfo;

protected:	
	AStar::BasePathFinder<PointInfo, CellType, CostInfo>* _pathFinderStart;
	AStar::BasePathFinder<PointInfo, CellType, CostInfo>* _pathFinderGoal;
	virtual bool IsGoal(NodeInfo& goal);
public:
	BidirectionalPathFinder(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map);
	~BidirectionalPathFinder();

	virtual void Init(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map);
	virtual void FindStart(NodeInfo start, NodeInfo goal);
	virtual NodeInfo FindStep();
	virtual bool FindIsPathExists(NodeInfo& node) ;
	virtual Path<PointInfo>* FindEnd(NodeInfo& curNode);

	virtual void InitDebug(MapView<PointInfo, CellType, NodeInfo, CostInfo>* mapForStateDebug)
	{
		_pathFinderStart->InitDebug(mapForStateDebug);
		_pathFinderGoal->InitDebug(mapForStateDebug);
	}
	virtual void ToOutputCurrentState();

};

#include "BidirectionalPathFinder.inl"

}

#endif //MOTIONPLAN_ASTAR_BIDIRECTIONALPATHFINDER_H
