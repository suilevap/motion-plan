#ifndef MOTIONPLAN_ASTAR_CELLQUEUE_H
#error "Include from CellQueue.h only."
#else

//#include <algorithm>

template<typename NodeInfo,typename CostInfo> 
CellQueue<NodeInfo, CostInfo>::CellQueue()
{
	_count = 0;
	_queue = new std::priority_queue<
		PathNode<NodeInfo,CostInfo>,
		std::vector<PathNode<NodeInfo,CostInfo>>,
		std::greater<PathNode<NodeInfo,CostInfo>> >();
}
template<typename NodeInfo,typename CostInfo> 
CellQueue<NodeInfo, CostInfo>::~CellQueue()
{
	delete _queue;
}

template<typename NodeInfo,typename CostInfo> 
void CellQueue<NodeInfo, CostInfo>::Push(const PathNode<NodeInfo, CostInfo>& node)
{

	_queue->push(node);
	_count++;
}

template<typename NodeInfo,typename CostInfo> 
PathNode<NodeInfo, CostInfo> CellQueue<NodeInfo, CostInfo>::Pop()
{

	PathNode<NodeInfo, CostInfo> result = _queue->top();
	_queue->pop();
	
	return result; 
}

template<typename NodeInfo,typename CostInfo> 
bool CellQueue<NodeInfo, CostInfo>::Empty()
{
	return _queue->empty();
}

template<typename NodeInfo,typename CostInfo> 
void CellQueue<NodeInfo, CostInfo>::Clear()
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