#pragma once

#ifndef MOTIONPLAN_ASTAR_PATHNODE_H
#define MOTIONPLAN_ASTAR_PATHNODE_H

namespace AStar
{

template<
	typename NodeInfo,
	typename CostInfo> 
struct PathNode
{

public:
	NodeInfo Node;
	CostInfo Distance;
	CostInfo EstimateDistance;
	CostInfo Rank;


	//Overload the < operator.
	bool operator< ( const PathNode<NodeInfo,CostInfo> &node2)
	{
		return Rank < node2.Rank;
	}

	//Overload the > operator.
	bool operator> ( const PathNode<NodeInfo,CostInfo> &node2)
	{
		return Rank > node2.Rank;
	}

	PathNode(NodeInfo node, CostInfo distance, CostInfo estimateDistance)
		:Node(node),
		Distance(distance),
		EstimateDistance(estimateDistance),
		Rank(distance+estimateDistance)
	{
	}

	PathNode();
};

////Overload the < operator.
template<
	typename NodeInfo,
	typename CostInfo> 
bool operator< (const PathNode<NodeInfo,CostInfo> &node1, const PathNode<NodeInfo,CostInfo> &node2)
{
	return node1.Rank < node2.Rank;
}
////Overload the > operator.
template<
	typename NodeInfo,
	typename CostInfo> 
bool operator> (const PathNode<NodeInfo,CostInfo> &node1, const PathNode<NodeInfo,CostInfo> &node2)
{
	return node1.Rank > node2.Rank;
}

#endif //MOTIONPLAN_ASTAR_PATHNODE_H
