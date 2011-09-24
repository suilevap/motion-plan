#ifndef MOTIONPLAN_ASTAR_QUADTREECELL_H_
#define MOTIONPLAN_ASTAR_QUADTREECELL_H_


namespace AStar
{

template<
	typename PointT, 
	typename CellType, 
	typename CostInfo = float> 
class QuadTreeCell
{
protected:
    int _childs[4];

public:
    QuadTreeCell();
    ~QuadTreeCell();
    
    void GetChild(int index);
}

    #include "QuadTreeCell.inl"
}

#endif //MOTIONPLAN_ASTAR_QUADTREECELL_H_
