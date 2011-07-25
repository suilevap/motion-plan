#pragma once

#ifndef MOTIONPLAN_ASTAR_MAPVIEW_H
#define MOTIONPLAN_ASTAR_MAPVIEW_H

#include <vector>
#include "Edge.h"
//#include "Point.h"

namespace AStar
{

template<
	typename PointInfo, 
	typename CellType, 
	typename NodeInfo, 
	typename CostInfo> 
class MapView
{
public:

	std::vector<Edge<NodeInfo,CostInfo>> GetNeighbors(NodeInfo& node);
	PointInfo GetPoint(NodeInfo& node);	
	NodeInfo GetNode(PointInfo& point);
	CellType GetCell(NodeInfo& node);
	void SetCell(NodeInfo& index, CellType cell);
	void SetCellRegion(PointInfo& point, CellType cell, PointInfo& size);
	PointInfo GetMaxPoint();
	NodeInfo GetMaxNode();

	
	CellType GetCell(PointInfo& point) {return GetCell(GetNode(point));}
	void SetCell(PointInfo& point, CellType cell) { SetCell(GetNode(point), cell);}
	
};

}

#endif //MOTIONPLAN_ASTAR_MAPVIEW_H
