#ifndef MOTIONPLAN_ASTAR_CELLQUEUE_H
#error "Include from CellQueue.h only."
#else

#include <algorithm>

namespace AStar
{

template<typename NodeInfo,typename CostInfo> 
CellQueue<NodeInfo, CostInfo>::CellQueue(float alphaDist)
{
	_alphaDist = alphaDist;
	_count = 0;
}

template<typename NodeInfo,typename CostInfo> 
void CellQueue<NodeInfo, CostInfo>::Push(const PathNode<NodeInfo, CostInfo>& node)
{

	_queue.push(point);
	_count++;
}

template<typename NodeInfo,typename CostInfo> 
PathPoint CellQueue<NodeInfo, CostInfo>::Pop()
{

	PathNode<NodeInfo, CostInfo> result = _queue.top();
	_queue.pop();
	
	return result; 
}

template<typename NodeInfo,typename CostInfo> 
bool CellQueue<NodeInfo, CostInfo>::Empty()
{
	return _queue.empty();
}

}

#endif