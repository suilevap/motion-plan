#pragma once

#ifndef MOTIONPLAN_ASTAR_PATH_H
#define MOTIONPLAN_ASTAR_PATH_H

#include <vector>
#include "MathHelper.h"

namespace AStar
{

template<typename PointInfo>
class Path
{
public:
    typedef int NodeInfo;

private:
	std::vector<PointInfo> _points;
	std::vector<NodeInfo> _nodes;
	
public:

	//Path(std::vector<NodeInfo>& nodes);
	Path();

	~Path(void);
	std::vector<PointInfo>& GetPoints();
	PointInfo GetPoint(int index);
	NodeInfo GetNode(int index);
	void SetPoint(int index, PointInfo point);


	int Count();	
	void Reverse();	

	void AddNodes(std::vector<NodeInfo>& nodes);
	void Add(PointInfo point, NodeInfo node);


	static Path* Empty();
	
};

#include "Path.inl"

}

#endif //MOTIONPLAN_ASTAR_PATH_H