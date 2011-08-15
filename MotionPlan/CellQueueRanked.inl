#ifndef MOTIONPLAN_ASTAR_CELLQUEUERANKED_H
#error "Include from CellQueueRanked.h only."
#else

//#include <algorithm>

template<typename NodeInfo,typename CostInfo> 
CellQueueRanked<NodeInfo, CostInfo>::CellQueueRanked()
{
	_count = 0;
	_queue = new std::priority_queue<
		PathNode<NodeInfo,CostInfo>,
		std::vector<PathNode<NodeInfo,CostInfo>>,
		std::greater<PathNode<NodeInfo,CostInfo>> >();
}
template<typename NodeInfo,typename CostInfo> 
CellQueueRanked<NodeInfo, CostInfo>::~CellQueueRanked()
{
	delete _queue;
}

template<typename NodeInfo,typename CostInfo> 
void CellQueueRanked<NodeInfo, CostInfo>::Push(const PathNode<NodeInfo, CostInfo>& node)
{

	_queue->push(node);
	_count++;
}

template<typename NodeInfo,typename CostInfo> 
PathNode<NodeInfo, CostInfo> CellQueueRanked<NodeInfo, CostInfo>::Pop()
{

	PathNode<NodeInfo, CostInfo> result = _queue->top();
	_queue->pop();
	
	return result; 
}

template<typename NodeInfo,typename CostInfo> 
bool CellQueueRanked<NodeInfo, CostInfo>::Empty()
{
	return _queue->empty();
}

template<typename NodeInfo,typename CostInfo> 
void CellQueueRanked<NodeInfo, CostInfo>::Clear()
{
	if (_queue != NULL)
	{
		delete _queue;
	}
	_queue = new std::priority_queue<
			PathNode<NodeInfo,CostInfo>,
			std::vector<PathNode<NodeInfo,CostInfo>>,
			std::greater<PathNode<NodeInfo,CostInfo>> >();
}


#endif