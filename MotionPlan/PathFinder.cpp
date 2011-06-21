#include "StdAfx.h"
#include <math.h>
#include <queue>
#include <algorithm>

#include "DistanceEvaluator.h"
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
	 _mapParent->SetCell(_start, _start);
	CellQueue* queue = new CellQueue();
	PathPoint point;
	point.Index = _start;
	point.Rank = 0;
	queue->push(point);

	bool pathFound = false;
	while (!queue->empty() && !pathFound)
	{
		//only for test
		//_mapDist->ToOutput();
		//_mapParent->ToOutputField();

		point = queue->top();
		queue->pop();
		int index = point.Index;
		if (index != _goal)
		{
			CheckNeighbor(index, -1, -1, queue);
			CheckNeighbor(index,  0, -1, queue);
			CheckNeighbor(index,  1, -1, queue);

			CheckNeighbor(index, -1,  0, queue);
			CheckNeighbor(index,  1,  0, queue);

			CheckNeighbor(index, -1,  1, queue);
			CheckNeighbor(index,  0,  1, queue);
			CheckNeighbor(index,  1,  1, queue);
		}
		else
		{
			pathFound = true;
			//only for test
			_mapParent->ToOutputField();
			_mapDist->ToOutput();
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
	
	reverse(result.begin(), result.end());
	return result;
}

bool PathFinder::CheckNeighbor(int index, int dx, int dy, CellQueue* queue)
{
	bool result;
	int newIndex = _map->GetCellIndex(index, dx, dy);
	float dist = GetDistance(index, dx , dy);
	result = CheckCell(newIndex, dist);
	if (result)
	{
		_mapParent->SetCell(newIndex, index);
		_mapDist->SetCell(newIndex, dist);

		PathPoint point;
		point.Index = newIndex;
		point.Rank = dist + GetEstimateDistance(newIndex);
		queue->push(point);
	}
	return result;
}

float PathFinder::GetEstimateDistance(int index)
{
	Point p = _map->GetCellPoint(index);
	return DistanceEvaluator::EuclideanDistance<float>(p.X, p.Y, _goalX, _goalY);
}

float PathFinder::GetDistance(int index, int dx, int dy)
{
	float result;
	float stepD;
	if ((dx!=0)&&(dy!=0))
	{
		stepD = sqrt(2.0f);
	}
	else
	{
		stepD = 1.0f;
	}

	//trick
	int parentDx;
	int parentDy;
	int parentIndex = _mapParent->GetCell(index);
	if (parentIndex != index)
	{
		_map->GetD(parentIndex, index, &parentDx,&parentDy);
		//diagonal
		if ((dx + dy + parentDx + parentDy) % 2 == 1)
		{
			int cell = _map->GetCellIndex(index, dx - parentDx, dy - parentDy);
			if (cell != 0)
			{
				stepD = sqrt(2.0f*2.0f + 1.0f);
				index = parentIndex;
			}
		}
	}
	result = _mapDist->GetCell(index) + stepD;
	return result;
}


bool PathFinder::CheckCell(int index, float curDist)
{
	bool result = false;
	if (_map->GetCell(index) !=0)
	{
		float d = _mapDist->GetCell(index);
		if ((_mapParent->GetCell(index) == 0) || (d > curDist))
		{			
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