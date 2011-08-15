#ifndef MOTIONPLAN_ASTAR_CELLQUEUERANKED_H
#define MOTIONPLAN_ASTAR_CELLQUEUERANKED_H

#include <queue>
#include <vector>
#include <set>
#include "PathNode.h"

//typedef priority_queue<PathPoint,vector<PathPoint>,less<vector<PathPoint>::value_type>> CellQueueRanked;
namespace AStar
{

template<
	typename NodeInfo,
	typename CostInfo> 
class CellQueueRanked 
{
private:
	/*std::priority_queue<
		PathNode<NodeInfo,CostInfo>,
		std::vector<PathNode<NodeInfo,CostInfo>>,
		std::greater<std::vector<PathNode<NodeInfo,CostInfo>>::value_type>> _queue;*/
	std::priority_queue<
		PathNode<NodeInfo,CostInfo>,
		std::vector<PathNode<NodeInfo,CostInfo>>,
		std::greater<PathNode<NodeInfo,CostInfo>> >* _queue;
	
	//std::vector<PathPoint> _unsortedQueue;

	float _alphaDist;

	int _count;

	//std::multiset<
	//	PathPoint,	
	//	std::less<PathPoint>> _set;
public:
	CellQueueRanked();
	~CellQueueRanked();


	void Push(const PathNode<NodeInfo,CostInfo>& point);
	PathNode<NodeInfo,CostInfo> Pop();
	bool Empty();

	void Clear();

};

#include "CellQueueRanked.inl"

}

#endif //MOTIONPLAN_ASTAR_CELLQUEUERANKED_H
