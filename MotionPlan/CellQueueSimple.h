#ifndef MOTIONPLAN_ASTAR_CELLQUEUESIMPLE_H
#define MOTIONPLAN_ASTAR_CELLQUEUESIMPLE_H

#include <queue>
#include "PathNode.h"

namespace AStar
{

template<
	typename NodeInfo,
	typename CostInfo> 
class CellQueueSimple 
{
private:

	std::queue<PathNode<NodeInfo,CostInfo>>* _queue;


	int _count;

public:
	CellQueueSimple();
	~CellQueueSimple();


	void Push(const PathNode<NodeInfo,CostInfo>& point);
	PathNode<NodeInfo,CostInfo> Pop();
	bool Empty();

	void Clear();

	static const bool UseHeuristic = false;
};

#include "CellQueueSimple.inl"

}

#endif //MOTIONPLAN_ASTAR_CELLQUEUESIMPLE_H
