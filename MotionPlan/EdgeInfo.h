#pragma once

#ifndef MOTIONPLAN_ASTAR_EDGE_H
#define MOTIONPLAN_ASTAR_EDGE_H

#include "NodeState.h"

namespace AStar
{

template<typename NodeInfo, typename CostInfo> 
struct EdgeInfo
{
public:
	//NodeInfo From;
	NodeInfo To;
	CostInfo Cost;
	NodeStatus::Status InitStatus;
	
	EdgeInfo()
		:To(0),
		Cost(0),
		InitStatus(NodeStatus::Open)
	{}

	EdgeInfo(NodeInfo node, CostInfo cost, NodeStatus::Status status)
		:To(node),
		Cost(cost),
		InitStatus(status)
	{}
};

}

#endif //MOTIONPLAN_ASTAR_EDGE_H
