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
//bool operator< (const PathPoint &point1, const PathPoint &point2);
////Overload the > operator.
//bool operator> (const PathPoint &point1, const PathPoint &point2);

}

#endif //MOTIONPLAN_ASTAR_PATHNODE_H
