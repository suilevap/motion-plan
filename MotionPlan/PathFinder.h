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
	typename CostInfo> 
class PathFinder
{

protected:	
	typedef int NodeInfo;

	MapView<PointInfo, CellType, CostInfo>* _map;
	NodeInfo _start;
	NodeInfo _goal;
    PointInfo _startP;
    PointInfo _goalP;

	//for debug
	MapView<PointInfo, CellType, CostInfo>* _mapForStateDebug;
	
	virtual bool IsGoal(NodeInfo goal) = 0;	
public:

	Path<PointInfo>* Find(PointInfo start, PointInfo goal)
	{
		_start = 0;
		_goal = 0;
		if (_map->OnMap(start))
		{
			_start = _map->GetNode(start);
            _startP = start;
		}
		if (_map->OnMap(goal))
		{
			_goal = _map->GetNode(goal);
            _goalP = goal;
		}

		FindStart(_start, _goal);

		NodeInfo curNode = _start;

		while (!IsGoal(curNode) && (curNode != NULL))
		{
			curNode = FindStep();
		}
		Path<PointInfo>* path = FindEnd(curNode);

		return path;
	}

	virtual ~PathFinder(){};
	virtual void Init(MapView<PointInfo, CellType, CostInfo>* map) = 0;
	virtual void FindStart(NodeInfo start, NodeInfo goal) = 0;
	virtual NodeInfo FindStep() = 0;
	virtual bool FindIsPathExists(NodeInfo node) = 0;
	virtual Path<PointInfo>* FindEnd(NodeInfo node) = 0;

	virtual void InitDebug(MapView<PointInfo, CellType, CostInfo>* mapForStateDebug)
	{
		_mapForStateDebug = mapForStateDebug; 
	}
	virtual void ToOutputCurrentState() = 0;

};

}

#endif //MOTIONPLAN_ASTAR_PATHFINDER_H
