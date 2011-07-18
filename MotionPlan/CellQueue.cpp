#include "StdAfx.h"
#include "CellQueue.h"

void CellQueue::Push(const PathPoint& point)
{
	_queue.push(point);
}

void CellQueue::Pop()
{
	_queue.pop();
}

PathPoint CellQueue::Top()
{
	return _queue.top();
}

bool CellQueue::Empty()
{
	return _queue.empty();
}
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
