#ifndef MOTIONPLAN_QUADNAVRECTMAPVIEW_H_
#error "Include from QuadNavRectMapView.h only."
#else

template<class CellType, typename CoordType>
QuadNavRectMapView<CellType, CoordType>::
QuadNavRectMapView(GridMapView<CellType, CoordType>* fromMap)
    :base(LoadFrom(fromMap))
{

}

template<class CellType, typename CoordType>
std::vector<Rectangle<CoordType>> QuadNavRectMapView<CellType, CoordType>::
LoadFrom(GridMapView<CellType, CoordType>* map)
{
    std::vector<Rectangle<CoordType>> result;



    return result;
}


template<class CellType, typename CoordType>
void QuadNavRectMapView<CellType, CoordType>::
AddQuadsFrom(Point<CoordType>& point1, Point<CoordType>& point2, std::vector<Rectangle<CoordType>>* rects, GridMapView<CellType, CoordType>* map)
{
    CellType cell;
    bool isIsotropic = map->IsCellRegionIsotropic(point1, point2, &cell)
    if (isIsotropic)
    {
        if (cell != 1)
        {
            rects->push_back(Rectangle<CoordType>(point1, point2));
        }            
    }
    else
    {
        Point<CoordType> pointCenter((point1.X + point2.X)/2,(point1.Y + point2.Y)/2) ;
        Point<CoordType> d = point2 - point1;
        if (d.X > map->GetCellSize()/2)
        {
        
        }
    }
}


#endif
