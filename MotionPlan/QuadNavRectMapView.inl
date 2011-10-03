#ifndef MOTIONPLAN_QUADNAVRECTMAPVIEW_H_
#error "Include from QuadNavRectMapView.h only."
#else

template<class CellType, typename CoordType>
QuadNavRectMapView<CellType, CoordType>*
QuadNavRectMapView<CellType, CoordType>::
Create(GridMapView<CellType, CoordType>* fromMap)
{
    QuadNavRectMapView<CellType, CoordType>* result = new QuadNavRectMapView<CellType, CoordType>();
    std::vector<AStar::Rectangle<CoordType>> rectangles = result->LoadFrom(fromMap);
    CoordType stepSize = fromMap->GetCellSize().X/2;
    result->Init(rectangles, stepSize);
    return result;
}

template<class CellType, typename CoordType>
std::vector<AStar::Rectangle<CoordType>> QuadNavRectMapView<CellType, CoordType>::
LoadFrom(GridMapView<CellType, CoordType>* map)
{
    std::vector<AStar::Rectangle<CoordType>> result;

    AddQuadsFrom(Point<CoordType>(0,0), map->GetMaxPoint(), &result, map);

    return result;
}


template<class CellType, typename CoordType>
void QuadNavRectMapView<CellType, CoordType>::
AddQuadsFrom(Point<CoordType> point1, Point<CoordType> point2, 
             std::vector<AStar::Rectangle<CoordType>>* rects, 
             GridMapView<CellType, CoordType>* map)
{
    AStar::Rectangle<CoordType> curRect(point1, point2);
    if (!curRect.IsEmpty(map->GetCellSize().X))
    {
        CellType cell;
        bool isIsotropic = map->IsCellRegionIsotropic(point1, point2, &cell);
        if (isIsotropic)
        {
            if (cell != 1)
            {
                rects->push_back(curRect);
            }            
        }
        else
        {
            Point<CoordType> pointCenter = Point<CoordType>::Avg(point1, point2);
            //round
            //TODO: fix black magic
            Point<CoordType> halsSellSize = map->GetCellSize()/2;
            pointCenter = map->GetPoint(map->GetNode(pointCenter-halsSellSize)) + halsSellSize;

            //split to 4 rects
            AddQuadsFrom(point1, pointCenter, 
                rects, map);
            AddQuadsFrom(Point<CoordType>(pointCenter.X, point1.Y), 
                Point<CoordType>(point2.X, pointCenter.Y), 
                rects, map);
            AddQuadsFrom(Point<CoordType>(point1.X, pointCenter.Y), 
                Point<CoordType>(pointCenter.X, point2.Y), 
                rects, map);
            AddQuadsFrom(pointCenter, point2, rects, map);
        }
    }
}


#endif
