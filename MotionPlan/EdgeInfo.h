#pragma once

#ifndef MOTIONPLAN_ASTAR_EDGE_H
#define MOTIONPLAN_ASTAR_EDGE_H

namespace AStar
{

template<typename NodeInfo, typename CostInfo> 
struct EdgeInfo
{
public:
	//NodeInfo From;
	NodeInfo To;
	CostInfo Cost;
	
	EdgeInfo(){}

	EdgeInfo(NodeInfo node, CostInfo cost)
		:To(node),
		Cost(cost)
	{}
};

}

#endif //MOTIONPLAN_ASTAR_EDGE_H
