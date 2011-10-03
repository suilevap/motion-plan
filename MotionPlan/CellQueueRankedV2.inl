#ifndef MOTIONPLAN_ASTAR_CELLQUEUERANKEDV2_H
#error "Include from CellQueueRankedV2.h only."
#else


template<typename NodeInfo,typename CostInfo> 
CellQueueRankedV2<NodeInfo, CostInfo>::CellQueueRankedV2()
{
	_count = 0;
	Clear();
}
template<typename NodeInfo,typename CostInfo> 
CellQueueRankedV2<NodeInfo, CostInfo>::~CellQueueRankedV2()
{
}

template<typename NodeInfo,typename CostInfo> 
void CellQueueRankedV2<NodeInfo, CostInfo>::
Push(PathNode<NodeInfo, CostInfo>* node)
{
    _queue.push_back(node);
    BubbleUp(_queue.size()-1, node);
	_count++;
}

template<typename NodeInfo,typename CostInfo> 
PathNode<NodeInfo, CostInfo>* CellQueueRankedV2<NodeInfo, CostInfo>::Pop()
{
    PathNode<NodeInfo, CostInfo>* result = _queue[0];
    TrickleDown(0, _queue[_queue.size()-1]);
    _queue.pop_back();
    return result;
}

template<typename NodeInfo,typename CostInfo> 
bool CellQueueRankedV2<NodeInfo, CostInfo>::Empty()
{
	return _queue.empty();
}

template<typename NodeInfo,typename CostInfo> 
void CellQueueRankedV2<NodeInfo, CostInfo>::Clear()
{
	_queue.clear();
}

template<typename NodeInfo,typename CostInfo> 
void CellQueueRankedV2<NodeInfo, CostInfo>::
BubbleUp(int i, PathNode<NodeInfo,CostInfo>* node)
{
    int parent = (i-1)/2;
    // note: (index > 0) means there is a parent
    while ((i > 0) && (*_queue[parent] > *node))
    {
        _queue[i] = _queue[parent];
        i = parent;
        parent = (i-1)/2;
    }
    _queue[i] = node;
}

template<typename NodeInfo,typename CostInfo> 
void CellQueueRankedV2<NodeInfo, CostInfo>::
TrickleDown(int i, PathNode<NodeInfo,CostInfo>* node)
{
    int child = (i*2)+1;
    int size = _queue.size();
    while (child < size)
    {
        if (((child+1) < size) && 
                (*_queue[child] > *_queue[child+1]))
        {
                child++;
        }
        _queue[i] = _queue[child];
        i = child;
        child = (i*2)+1;
    }
    BubbleUp(i, node);
}

#endif