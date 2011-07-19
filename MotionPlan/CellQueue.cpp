#include "StdAfx.h"
#include "CellQueue.h"
#include <algorithm>


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

//CellQueue::CellQueue(float alphaDist)
//{
//	_alphaDist = alphaDist;
//	_count = 0;
//	_sum = 0;
//	_missed = 0;
//}
//
//void CellQueue::Push(const PathPoint& point)
//{
//	if (point.Rank < _sum/_count*_alphaDist)
//	{
//		_queue.push(point);
//	}
//	else
//	{
//		_unsortedQueue.push_back(point);
//	}
//	_count++;
//	_sum+=point.Rank;
//}
//
//PathPoint CellQueue::Pop()
//{
//	PathPoint result;
//	if (!_queue.empty())
//	{
//		result = _queue.top();
//		_queue.pop();
//	}
//	else
//	{
//		std::vector<PathPoint>::iterator it = std::min_element( _unsortedQueue.begin(), _unsortedQueue.end() );
//		result = *it;
//		_unsortedQueue.erase(it);
//		_missed++;
//	}
//	_min = result.Rank;
//
//	return result; 
//}
//
//bool CellQueue::Empty()
//{
//	return _queue.empty() && _unsortedQueue.empty();
//}
//
//void CellQueue::Push(const PathPoint& point)
//{
//	_set.insert(point);
//}
//
//void CellQueue::Pop()
//{
//	_set.erase(_set.begin());
//}
//
//PathPoint CellQueue::Top()
//{
//	return *_set.begin();
//}
//
//bool CellQueue::Empty()
//{
//	return _set.empty();
//}
