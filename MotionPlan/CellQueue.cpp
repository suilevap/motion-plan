#include "StdAfx.h"
#include "CellQueue.h"
#include <algorithm>

namespace AStar
{

CellQueue::CellQueue(float alphaDist)
{
	_alphaDist = alphaDist;
	_count = 0;
}

void CellQueue::Push(const PathPoint& point)
{

	_queue.push(point);
	_count++;
}

PathPoint CellQueue::Pop()
{

	PathPoint result = _queue.top();
	_queue.pop();
	
	return result; 
}

bool CellQueue::Empty()
{
	return _queue.empty();
}

}