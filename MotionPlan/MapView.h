#pragma once

#ifndef MOTIONPLAN_ASTAR_MAPVIEW_H
#define MOTIONPLAN_ASTAR_MAPVIEW_H

#include <vector>
#include "EdgeInfo.h"
//#include "Point.h"

namespace AStar
{

template<
	typename PointInfo, 
	typename CellType, 
	typename NodeInfo = int, 
	typename CostInfo = float> 
class MapView
{
public:

	virtual void GetNeighbors(NodeInfo& node, std::vector<EdgeInfo<NodeInfo,CostInfo>>& neighbors) = 0;
	virtual PointInfo GetPoint(NodeInfo& node)= 0;	
	virtual NodeInfo GetNode(PointInfo& point)= 0;
	virtual CellType GetCell(NodeInfo& node)= 0;
	virtual void SetCell(NodeInfo& index, CellType cell)= 0;
	virtual void SetCellRegion(PointInfo& point, CellType cell, PointInfo& size)= 0;
	virtual PointInfo GetMaxPoint()= 0;
	virtual NodeInfo GetMaxNode()= 0;
	virtual CostInfo GetCost(NodeInfo& node1, NodeInfo& node2) = 0;
	
	CellType GetCellPoint(PointInfo& point)
	{
		NodeInfo node = GetNode(point);
		CellType cell = GetCell(node);
		return cell;
	}
	void SetCellPoint(PointInfo& point, CellType cell)
	{
		NodeInfo node = GetNode(point);
		SetCell(node, cell);
	}
	
};

}

#endif //MOTIONPLAN_ASTAR_MAPVIEW_H
