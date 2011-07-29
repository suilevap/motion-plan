#pragma once

#ifndef MOTIONPLAN_ASTAR_NODESTATE_H
#define MOTIONPLAN_ASTAR_NODESTATE_H

namespace AStar
{

template<
	typename NodeInfo,
	typename CostInfo> 
struct NodeState
{

public:
	NodeInfo ParentNode;
	CostInfo Cost;

	NodeState(const NodeInfo& parent,const CostInfo& cost):
		ParentNode(parent),
		Cost(cost)
	{
	}

	NodeState():
		ParentNode(0),
		Cost(0)
	{
	}
};


}
#endif //MOTIONPLAN_ASTAR_NODESTATE_H
