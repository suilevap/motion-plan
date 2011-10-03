#pragma once

#ifndef MOTIONPLAN_ASTAR_BIDIRECTIONALPATHFINDER_H
#define MOTIONPLAN_ASTAR_BIDIRECTIONALPATHFINDER_H

#include "MapView.h"
#include <vector>
#include "PathNode.h"

#include "EdgeInfo.h"
#include "Path.h"
#include "NodeState.h"
#include "CellQueueRanked.h"
#include "CellQueueSimple.h"


namespace AStar
{

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueueStart = CellQueueSimple<int, CostInfo>,
	typename CellQueueGoal = CellQueueSimple<int, CostInfo>> 
class BidirectionalPathFinder: public AStar::PathFinder<PointInfo, CellType,  CostInfo>
{
public:
	typedef int NodeInfo;

protected:	
	AStar::BasePathFinder<PointInfo, CellType, CostInfo, CellQueueStart>* _pathFinderStart;
	AStar::BasePathFinder<PointInfo, CellType, CostInfo, CellQueueGoal>* _pathFinderGoal;
	virtual bool IsGoal(NodeInfo goal);
public:
	BidirectionalPathFinder(MapView<PointInfo, CellType, CostInfo>* map);
	~BidirectionalPathFinder();

	virtual void Init(MapView<PointInfo, CellType, CostInfo>* map);
	virtual void FindStart(NodeInfo start, NodeInfo goal);
	virtual NodeInfo FindStep();
	virtual bool FindIsPathExists(NodeInfo node) ;
	virtual Path<PointInfo>* FindEnd(NodeInfo curNode);

	virtual void InitDebug(MapView<PointInfo, CellType, CostInfo>* mapForStateDebug)
	{
		_pathFinderStart->InitDebug(mapForStateDebug);
		_pathFinderGoal->InitDebug(mapForStateDebug);
	}
	virtual void ToOutputCurrentState();

};

#include "BidirectionalPathFinder.inl"

}

#endif //MOTIONPLAN_ASTAR_BIDIRECTIONALPATHFINDER_H
