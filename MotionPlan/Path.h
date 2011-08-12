#pragma once

#ifndef MOTIONPLAN_ASTAR_PATH_H
#define MOTIONPLAN_ASTAR_PATH_H

#include <vector>

namespace AStar
{

template<typename PointInfo>
class Path
{
private:
	std::vector<PointInfo> _points;
	
public:
	Path(std::vector<PointInfo> points);
	~Path(void);
	std::vector<PointInfo>& GetPoints();
	PointInfo GetPoint(int index);
	int Count();	

	void AddPoints(std::vector<PointInfo>& points);

	static Path* Empty();
	
};

#include "Path.inl"

}

#endif //MOTIONPLAN_ASTAR_PATH_H