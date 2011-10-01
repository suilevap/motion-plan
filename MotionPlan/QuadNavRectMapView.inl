#ifndef MOTIONPLAN_QUADNAVRECTMAPVIEW_H_
#error "Include from QuadNavRectMapView.h only."
#else

template<class CellType, typename CoordType, bool UseFastNodeSearch>
QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>*
QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>::
Create(GridMapView<CellType, CoordType>* fromMap)
{
    QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>* result = new QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>();
    std::vector<AStar::Rectangle<CoordType>> rectangles = result->LoadFrom(fromMap);
    CoordType stepSize = fromMap->GetCellSize().X/2;
    result->Init(rectangles, stepSize);
    return result;
}

template<class CellType, typename CoordType, bool UseFastNodeSearch>
std::vector<AStar::Rectangle<CoordType>> QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>::
LoadFrom(GridMapView<CellType, CoordType>* map)
{
    if (UseFastNodeSearch)
    {
        _fastNodeSearch = new GridMapView<int, CoordType>(
            map->GetMaxPoint().X, map->GetMaxPoint().Y, map->GetCellSize().X);
    }
    std::vector<AStar::Rectangle<CoordType>> result;
    _cellSize = map->GetCellSize();
    _root = AddQuadsFrom(Point<CoordType>(0,0), map->GetMaxPoint(), &result, map);
    
    return result;
}

template<class CellType, typename CoordType, bool UseFastNodeSearch>
typename QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>::QuadTreeNode* 
QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>::
AddQuadsFrom(Point<CoordType> point1, Point<CoordType> point2, 
             std::vector<AStar::Rectangle<CoordType>>* rects, 
             GridMapView<CellType, CoordType>* map)
{
    QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>::QuadTreeNode* result = NULL;
    AStar::Rectangle<CoordType> curRect(point1, point2);
    if (!curRect.IsEmpty(map->GetCellSize().X))
    {
        result = new QuadTreeNode();

        CellType cell;
        bool isIsotropic = map->IsCellRegionIsotropic(point1, point2, &cell);
        if (isIsotropic)
        {
            if (cell != 1)
            {
                rects->push_back(curRect);
                int id = rects->size();
                if (UseFastNodeSearch)
                {
                    _fastNodeSearch->SetCellRegion(point1, id, point2-point1);
                }
                else
                {
                    result->NavRectId = id;
                }
            }            
        }
        else
        {
            Point<CoordType> pointCenter = Point<CoordType>::Avg(point1, point2);
            //round
            //TODO: fix black magic
            Point<CoordType> halfCellSize = map->GetCellSize()/2;
            pointCenter = map->GetPoint(map->GetNode(pointCenter-halfCellSize)) + halfCellSize;

            //split to 4 rects
            result->Childs[0] = AddQuadsFrom(point1, pointCenter, 
                rects, map);
            result->Childs[1] = AddQuadsFrom(Point<CoordType>(pointCenter.X, point1.Y), 
                Point<CoordType>(point2.X, pointCenter.Y), 
                rects, map);
            result->Childs[2] = AddQuadsFrom(Point<CoordType>(point1.X, pointCenter.Y), 
                Point<CoordType>(pointCenter.X, point2.Y), 
                rects, map);
            result->Childs[3] = AddQuadsFrom(pointCenter, point2, rects, map);
        }
    }
    return result;
}

template<class CellType, typename CoordType, bool UseFastNodeSearch>
int QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>::
GetNode(Point<CoordType>& point)
{
    if (UseFastNodeSearch)
    {
        return _fastNodeSearch->GetCellPoint(point);
    }
    //return base::GetNode(point);

    int result = -1;
    QuadTreeNode* node = _root;
    Point<CoordType> pointCenter;
    Point<CoordType> point1 = _global.GetLeftTopPoint();
    Point<CoordType> point2 = _global.GetRightBottomPoint();
    AStar::Rectangle<CoordType> curRect = _global;

    while (node!= NULL && node->NavRectId <= 0)
    {
        pointCenter = Point<CoordType>::Avg(point1, point2);
        //round
        //TODO: fix black magic
        pointCenter.X = (static_cast<int>(pointCenter.X/_cellSize.X-0.5)+1)*_cellSize.X;
        pointCenter.Y = (static_cast<int>(pointCenter.Y/_cellSize.Y-0.5)+1)*_cellSize.Y;
        if (point.X < pointCenter.X)
        {
            point2.X = pointCenter.X;
        }
        else
        {
            point1.X = pointCenter.X;
        }
        if (point.Y < pointCenter.Y)
        {
            point2.Y = pointCenter.Y;
        }
        else
        {
            point1.Y = pointCenter.Y;
        }
        node = node->GetChild(point, pointCenter);

    }
    if (node != NULL)
    {
        result = node->NavRectId;
    }
    return result;
}

#endif
