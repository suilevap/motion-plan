#include <queue>
#include <vector>
#include "PathPoint.h"

//typedef priority_queue<PathPoint,vector<PathPoint>,less<vector<PathPoint>::value_type>> CellQueue;

class CellQueue: public std::priority_queue<
							PathPoint,
							std::vector<PathPoint>,
							std::less<std::vector<PathPoint>::value_type>>
{

};
