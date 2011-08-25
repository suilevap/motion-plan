#ifndef MOTIONPLAN_ASTAR_CELLQUEUESIMPLE_H
#error "Include from CellQueueSimple.h only."
#else

template<typename NodeInfo,typename CostInfo> 
CellQueueSimple<NodeInfo, CostInfo>::CellQueueSimple()
{
	_count = 0;
	_queue = NULL;
	Clear();
}
template<typename NodeInfo,typename CostInfo> 
CellQueueSimple<NodeInfo, CostInfo>::~CellQueueSimple()
{
	delete _queue;
}

template<typename NodeInfo,typename CostInfo> 
void CellQueueSimple<NodeInfo, CostInfo>::Push(const PathNode<NodeInfo, CostInfo>& node)
{

	_queue->push(node);
	_count++;
}

template<typename NodeInfo,typename CostInfo> 
PathNode<NodeInfo, CostInfo> CellQueueSimple<NodeInfo, CostInfo>::Pop()
{

	PathNode<NodeInfo, CostInfo> result = _queue->front();
	_queue->pop();
	
	return result; 
}

template<typename NodeInfo,typename CostInfo> 
bool CellQueueSimple<NodeInfo, CostInfo>::Empty()
{
	return _queue->empty();
}

template<typename NodeInfo,typename CostInfo> 
void CellQueueSimple<NodeInfo, CostInfo>::Clear()
{
	if (_queue != NULL)
	{
		delete _queue;
	}
	
	_queue = new std::queue<PathNode<NodeInfo,CostInfo>>();
	
}


#endif