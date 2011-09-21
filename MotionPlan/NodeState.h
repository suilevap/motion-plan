#pragma once

#ifndef MOTIONPLAN_ASTAR_NODESTATE_H
#define MOTIONPLAN_ASTAR_NODESTATE_H

namespace AStar
{

	namespace NodeStatus
	{
		enum Status
		{
			Open=0,
			Close
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
		Status(NodeStatus::Open)
	{
	}

	NodeState():
		ParentNode(0),
		Cost(0),
		Status(NodeStatus::Open)
	{
	}
};


}
#endif //MOTIONPLAN_ASTAR_NODESTATE_H
