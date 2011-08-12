#pragma once

#ifndef MOTIONPLAN_ASTAR_PATHFINDER_H
#define MOTIONPLAN_ASTAR_PATHFINDER_H

#include "MapView.h"
#include "Path.h"

namespace AStar
{

template<
	typename PointInfo, 
	typename CellType, 	
	typename NodeInfo,
	typename CostInfo> 
class PathFinder
{
protected:	
	MapView<PointInfo, CellType, NodeInfo, CostInfo>* _map;
	NodeInfo _start;
	NodeInfo _goal;

	//for debug
	MapView<PointInfo, CellType, NodeInfo, CostInfo>* _mapForStateDebug;
	
	virtual bool IsGoal(NodeInfo& goal) = 0;	
public:

	Path<PointInfo>* Find(PointInfo start, PointInfo goal)
	{
		_start = _map->GetNode(start);
		_goal = _map->GetNode(goal);
		FindStart(_start, _goal);

		NodeInfo curNode = _start;

		while (!IsGoal(curNode) && (curNode != NULL))
		{
			curNode = FindStep();
		}
		Path<PointInfo>* path = FindEnd(curNode);

		return path;
	}

	virtual void Init(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map) = 0;
	virtual void FindStart(NodeInfo start, NodeInfo goal) = 0;
	virtual NodeInfo FindStep() = 0;
	virtual bool FindIsPathExists(NodeInfo& node) = 0;
	virtual Path<PointInfo>* FindEnd(NodeInfo& node) = 0;

	virtual void InitDebug(MapView<PointInfo, CellType, NodeInfo, CostInfo>* mapForStateDebug)
	{
		_mapForStateDebug = mapForStateDebug; 
	}
	virtual void ToOutputCurrentState() = 0;

};

}

#endif //MOTIONPLAN_ASTAR_PATHFINDER_H
