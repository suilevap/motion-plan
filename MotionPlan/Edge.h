#pragma once

#ifndef MOTIONPLAN_ASTAR_EDGE_H
#define MOTIONPLAN_ASTAR_EDGE_H

namespace AStar
{

template<typename NodeInfo, typename CostInfo> 
struct Edge
{
public:
	//NodeInfo From;
	NodeInfo To;
	CostInfo Cost;
	
	Edge(){}

	Edge(NodeInfo node, CostInfo cost)
		:To(node),
		Cost(cost)
	{}
};

}

#endif //MOTIONPLAN_ASTAR_EDGE_H
