//
// Used part of code from recastnavigation (http://code.google.com/p/recastnavigation/source/browse/trunk/Detour/Include/DetourNode.h)
//
#ifndef MOTIONPLAN_ASTAR_CELLQUEUERANKEDV2_H
#define MOTIONPLAN_ASTAR_CELLQUEUERANKEDV2_H

#include <vector>
#include "PathNode.h"

namespace AStar
{

template<
	typename NodeInfo,
	typename CostInfo> 
class CellQueueRankedV2 
{
private:

	std::vector<PathNode<NodeInfo,CostInfo>> _queue;

	int _count;

    void BubbleUp(int i,const PathNode<NodeInfo,CostInfo>& point);
    void TrickleDown(int i,const PathNode<NodeInfo,CostInfo>& point);

public:
	CellQueueRankedV2();
	~CellQueueRankedV2();

	void Push(const PathNode<NodeInfo,CostInfo>& point);
	PathNode<NodeInfo,CostInfo> Pop();
	bool Empty();

	void Clear();

	static const bool UseHeuristic = true;
};

#include "CellQueueRankedV2.inl"

}

#endif //MOTIONPLAN_ASTAR_CELLQUEUERANKEDV2_H
