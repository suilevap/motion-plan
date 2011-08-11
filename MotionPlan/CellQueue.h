#ifndef MOTIONPLAN_ASTAR_CELLQUEUE_H
#define MOTIONPLAN_ASTAR_CELLQUEUE_H

#include <queue>
#include <vector>
#include <set>
#include "PathNode.h"

//typedef priority_queue<PathPoint,vector<PathPoint>,less<vector<PathPoint>::value_type>> CellQueue;
namespace AStar
{

template<
	typename NodeInfo,
	typename CostInfo> 
class CellQueue 
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
	CellQueue();
	~CellQueue();


	void Push(const PathNode<NodeInfo,CostInfo>& point);
	PathNode<NodeInfo,CostInfo> Pop();
	bool Empty();

	void Clear();

};

#include "CellQueue.inl"

}

#endif //MOTIONPLAN_ASTAR_CELLQUEUE_H
