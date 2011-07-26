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

	virtual std::vector<Edge<NodeInfo,CostInfo>>& GetNeighbors(NodeInfo& node) = 0;
	virtual PointInfo GetPoint(NodeInfo& node)= 0;	
	virtual NodeInfo GetNode(PointInfo& point)= 0;
	virtual CellType GetCell(NodeInfo& node)= 0;
	virtual void SetCell(NodeInfo& index, CellType cell)= 0;
	virtual void SetCellRegion(PointInfo& point, CellType cell, PointInfo& size)= 0;
	virtual PointInfo GetMaxPoint()= 0;
	virtual NodeInfo GetMaxNode()= 0;

	
	CellType GetCell(PointInfo& point) {return GetCell(GetNode(point));}
	void SetCell(PointInfo& point, CellType cell) { SetCell(GetNode(point), cell);}
	
};

}

#endif //MOTIONPLAN_ASTAR_MAPVIEW_H
