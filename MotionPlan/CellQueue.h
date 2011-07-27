#include <queue>
#include <vector>
#include <set>
#include "PathPoint.h"

//typedef priority_queue<PathPoint,vector<PathPoint>,less<vector<PathPoint>::value_type>> CellQueue;
namespace AStar
{

class CellQueue 
{
private:
	std::priority_queue<
		PathPoint,
		std::vector<PathPoint>,
		std::greater<std::vector<PathPoint>::value_type>> _queue;
	
	//std::vector<PathPoint> _unsortedQueue;

	float _alphaDist;

	int _count;

	//std::multiset<
	//	PathPoint,	
	//	std::less<PathPoint>> _set;
public:
	CellQueue(float alphaDist);

	void Push(const PathPoint& point);
	PathPoint Pop();

	bool Empty();
};

}