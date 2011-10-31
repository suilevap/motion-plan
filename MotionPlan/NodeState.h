#pragma once

#ifndef MOTIONPLAN_ASTAR_NODESTATE_H
#define MOTIONPLAN_ASTAR_NODESTATE_H

namespace AStar
{

	namespace NodeStatus
	{
		enum Status
		{
            Free=0,
			Open=1,
			Close=2
		};
	}

template<
	typename NodeInfo,
	typename CostInfo> 
struct NodeState
{

public:	

	NodeInfo ParentNode;
	CostInfo Cost;
	NodeStatus::Status Status;

	NodeState(const NodeInfo parent,const CostInfo& cost):
		ParentNode(parent),
		Cost(cost),
		Status(NodeStatus::Free)
	{
	}

	NodeState():
		ParentNode(0),
		Cost(0),
		Status(NodeStatus::Free)
	{
	}
};


}
#endif //MOTIONPLAN_ASTAR_NODESTATE_H
