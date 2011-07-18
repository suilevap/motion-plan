#include <queue>
#include <vector>
#include <set>
#include "PathPoint.h"

//typedef priority_queue<PathPoint,vector<PathPoint>,less<vector<PathPoint>::value_type>> CellQueue;

class CellQueue 
{
private:
	std::priority_queue<
		PathPoint,
		std::vector<PathPoint>,
		std::greater<std::vector<PathPoint>::value_type>> _queue;

	std::multiset<
		PathPoint,	
		std::less<PathPoint>> _set;
public:
	void Push(const PathPoint& point);
	void Pop();
	PathPoint Top();
	bool Empty();
};
