#include "StdAfx.h"
#include <math.h>
#include <queue>
#include <algorithm>

#include "DistanceEvaluator.h"
#include "PathFinder.h"
#include "MathConstants.h"


PathFinder::PathFinder(Map<int>* map)
{
	_map = map;
	_mapDist = new Map<float>(map);
	_mapParent = new Map<int>(map);
}

PathFinder::~PathFinder(void)
{
	delete _mapDist;
	delete _mapParent;
}

Path* PathFinder::Find(int x, int y, int goalX, int goalY, float estimateAlpha)
{	
	_goalX = goalX;
	_goalY = goalY;
	_start = _map->GetCellIndex(x, y);
	_goal = _map->GetCellIndex(_goalX, _goalY);
	//TODO: fix several return!!
	if ((_map->GetCell(_start) == 1) ||(_map->GetCell(_goal) == 1))
	{
		return Path::Empty();
	}

	_mapDist->Clear(0, 0);
	_mapParent->Clear(0, 0);
	//float estimateDist = GetEstimateDistance(_start) * estimateAlpha*0+155;
	_queue = new CellQueue(estimateAlpha);

	 _mapParent->SetCell(_start, _start);

	PathPoint point(_start, 0, 0);

	_queue->Push(point);

	bool pathFound = false;
	while (!_queue->Empty() && !pathFound)
	{
		//only for test
		//_mapDist->ToOutput();
		//_mapParent->ToOutputField();
	
		point = _queue->Pop();
		int index = point.Index;
		if (index != _goal)
		{
			Step(index);
		}
		else
		{
			pathFound = true;
			//only for test
			//_mapParent->ToOutputField();
			//_mapDist->ToOutput();
		}
	}

	delete _queue;

	Path* result;
	if (pathFound)
	{
		result = ExtractPath();
	}
	else
	{
		result = Path::Empty();
	}
	return result;
}

void PathFinder::Step(int index)
{
	CheckNeighbor(index, -1, -1);
	CheckNeighbor(index,  0, -1);
	CheckNeighbor(index,  1, -1);

	CheckNeighbor(index, -1,  0);
	CheckNeighbor(index,  1,  0);

	CheckNeighbor(index, -1,  1);
	CheckNeighbor(index,  0,  1);
	CheckNeighbor(index,  1,  1);
}

Path* PathFinder::ExtractPath()
{
	Point point;
	
	std::vector<Point> result;
	int pos = _goal;
	
	result.push_back(_map->GetCellPoint(_goal));
	while (pos != _start)
	{
		pos = _mapParent->GetCell(pos);
		result.push_back(_map->GetCellPoint(pos));
	}
	
	reverse(result.begin(), result.end());
	Path* path = new Path(result);
	return path;
}

bool PathFinder::CheckNeighbor(int index, int dx, int dy)
{
	bool result = false;
	int newIndex = _map->GetCellIndex(index, dx, dy);
	if (_map->GetCell(newIndex) == 0)
	{
		float dist = GetDistance(index, dx , dy);

		if ((_mapParent->GetCell(newIndex) == 0) 
			|| (_mapDist->GetCell(newIndex) > dist))
		{
			_mapParent->SetCell(newIndex, index);
			_mapDist->SetCell(newIndex, dist);

			float estimate = GetEstimateDistance(newIndex);
			PathPoint point(newIndex, dist, estimate );
			_queue->Push(point);
			result = true;
		}
	}
	return result;
}

float PathFinder::GetEstimateDistance(int index)
{
	Point p = _map->GetCellPoint(index);
	float result = DistanceEvaluator::DiagonalDistance<float>(p.X, p.Y, _goalX, _goalY);
	return result;
}

float PathFinder::GetDistance(int index, int dx, int dy)
{
	float result;
	float stepD;
	if ((dx!=0)&&(dy!=0))
	{
		stepD = SQRT_2;
	}
	else
	{
		stepD = 1.0f;
	}

	////Theta* trick
	//int parentIndex = _mapParent->GetCell(index);
	//if (parentIndex != index)
	//{	
	//	//get middle cell between point and grandparent point
	//	int cellIdx = _map->GetCellIndex(parentIndex, dx, dy);
	//	//check that middle point is not our parent, and that it cell is clear
	//	if ((cellIdx != index) && (_map->GetCell(cellIdx)==0))
	//	{
	//		stepD = SQRT_5;//sqrt(2.0f*2.0f + 1.0f);
	//		index = parentIndex;
	//	}
	//}
	result = _mapDist->GetCell(index) + stepD;
	return result;
}



