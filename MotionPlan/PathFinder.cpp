#include "StdAfx.h"
#include <queue>
#include <algorithm>

#include "PathFinder.h"

PathFinder::PathFinder(Map<int>* map)
{
	_map = map;
	_mapDist = new Map<float>(map->GetWidth(), map->GetHeight());
	_mapParent = new Map<int>(map->GetWidth(), map->GetHeight());
}

PathFinder::~PathFinder(void)
{
	delete _mapDist;
	delete _mapParent;
}

std::vector<Point> PathFinder::Find(int x, int y, int goalX, int goalY)
{
	_goalX = goalX;
	_goalY = goalY;
	_start = _map->GetCellIndex(x, y);
	_goal = _map->GetCellIndex(_goalX, _goalY);
	CellQueue* queue = new CellQueue();
	PathPoint point;
	point.Index = _start;
	point.Rank = 0;
	queue->push(point);

	bool pathFound = false;
	while (!queue->empty() && !pathFound)
	{
		point = queue->top();
		queue->pop();
		int index = point.Index;
		if (index != _goal)
		{
			CheckNeighbor(index, -1, -1, queue);
			CheckNeighbor(index,  0, -1, queue);
			CheckNeighbor(index,  1, -1, queue);

			CheckNeighbor(index, -1,  0, queue);
			CheckNeighbor(index,  0,  0, queue);
			CheckNeighbor(index,  1,  0, queue);

			CheckNeighbor(index, -1,  1, queue);
			CheckNeighbor(index,  0,  1, queue);
			CheckNeighbor(index,  1,  1, queue);
		}
		else
		{
			pathFound = true;
		}
	}

	delete queue;

	std::vector<Point> result;
	if (pathFound)
	{
		result = ExtractPath();
	}
	return result;
}

std::vector<Point> PathFinder::ExtractPath()
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
	result.push_back(_map->GetCellPoint(_start));
	reverse(result.begin(), result.end());
	return result;
}

bool PathFinder::CheckNeighbor(int index, int dx, int dy, CellQueue* queue)
{
	bool result;
	float curDist= _mapDist->GetCell(index);
	int newIndex = _map->GetCellIndex(index, dx, dy);
	float dist = curDist + GetStepDistance(index, dx , dy);
	result = CheckCell(newIndex, dist);
	if (result)
	{
		PathPoint point;
		point.Index = newIndex;
		point.Rank = dist + GetEstimateDistance(newIndex);
		queue->push(point);
	}
	return result;
}

float PathFinder::GetEstimateDistance(int index)
{
	return 0;
}

float PathFinder::GetStepDistance(int index, int dx, int dy)
{
	float result;
	if ((dx!=0)&&(dy!=0))
	{
		result = 1.41f;
	}
	else
	{
		result = 1.0f;
	}
	return result;
}


bool PathFinder::CheckCell(int index, float curDist)
{
	bool result = false;
	if (_map->GetCell(index) !=0)
	{
		if (_mapDist->GetCell(index) > curDist)
		{
			_mapDist->SetCell(index, curDist);
			result = true;
		}
	}
	return result;
}

//void PathFinder::DirToXY(int dir, int* x, int* y)
//{
//	*x = dir & 0x03 - 1;
//	*y = (dir>>2) & 0x03 - 1;
//}
//int PathFinder::XYToDir(int x, int y)
//{
//	return (x+1)|((y+1)<<2);
//}

//float PathFinder::ComputeCost(int x0, int y0, int x1, int y1)
//{
//	
//}
//float PathFinder::GetParentDist(int x, int y)
//{
//
//	return 0;//_mapDist->GetCell(_mapParent->GetCell(x, y)
//}
