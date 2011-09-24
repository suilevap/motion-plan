#ifndef MOTIONPLAN_ASTAR_QUADTREECELL_H_
#error "Include from QuadTreeCell.h only."
#else
    
template<
typename PointT, 
typename CellType, 
typename CostInfo> 
int QuadTreeCell<PointT, CellType, CostInfo>::GetChild(int index)
{
    return _childs[index];
}

#endif
