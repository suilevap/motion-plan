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
    inline PointInfo GetStartPoint(){ return _startP;}
    inline PointInfo GetGoalPoint(){ return _goalP;}
    

    inline MapView<PointInfo, CellType, CostInfo>* GetMap(){return _map;}

	Path<PointInfo>* Find(PointInfo start, PointInfo goal)
	{
		_start = 0;
		_goal = 0;
		if (!_map->OnMap(start))
            return Path<PointInfo>::Empty();
		if (!_map->OnMap(goal))
            return Path<PointInfo>::Empty();

		_start = _map->GetNode(start);
        if (_start <= 0)
            return Path<PointInfo>::Empty();
        _startP = start;

		_goal = _map->GetNode(goal);
        if (_goal <= 0)
            return Path<PointInfo>::Empty();
        _goalP = goal;

		FindStart(start, goal);

		NodeInfo curNode = _start;
		do
        {
			curNode = FindStep();
		}
		while (!IsGoal(curNode) && (curNode != NULL));
        
		Path<PointInfo>* path = FindEnd(goal);

		return path;
	}

	virtual ~PathFinder(){};
	virtual void Init(MapView<PointInfo, CellType, CostInfo>* map) = 0;
	virtual void FindStart(PointInfo start, PointInfo goal) = 0;
	virtual NodeInfo FindStep() = 0;
	virtual bool FindIsPathExists(NodeInfo node) = 0;
	virtual Path<PointInfo>* FindEnd(PointInfo node) = 0;

	virtual void InitDebug(MapView<PointInfo, CellType, CostInfo>* mapForStateDebug)
	{
		_mapForStateDebug = mapForStateDebug; 
	}
	virtual void ToOutputCurrentState() = 0;

};

}

#endif //MOTIONPLAN_ASTAR_PATHFINDER_H
