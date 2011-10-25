#ifndef MOTIONPLAN_FIELDNAVRECTMAPVIEW_H_
#error "Include from FieldNavRectMapView.h only."
#else


template<class CellType, typename CoordType>
FieldNavRectMapView<CellType, CoordType>* 
FieldNavRectMapView<CellType, CoordType>::
Create(GridMapView<CellType, CoordType>* fromMap)
{
    FieldNavRectMapView<CellType, CoordType>* result = new FieldNavRectMapView<CellType, CoordType>();

    std::vector<AStar::Rectangle<CoordType>> rectangles = result->LoadFrom(fromMap);
    CoordType stepSize = fromMap->GetCellSize().X/2;
    result->Init(rectangles, stepSize);
    return result;
}

template<class CellType, typename CoordType>
std::vector<AStar::Rectangle<CoordType>> 
FieldNavRectMapView<CellType, CoordType>::
LoadFrom(GridMapView<CellType, CoordType>* map)
{
    std::vector<AStar::Rectangle<CoordType>> result;
    _cellSize = map->GetCellSize();
    GridMapView<int, CoordType>* distanceFieldMap = map->GetDistanceField();

    std::vector<int> distanceFieldVector;
    int width = distanceFieldMap->ToVector(&distanceFieldVector);
    int height = distanceFieldVector.size() / width;
    //simple 2d representation
    Vector2D<int> distanceField(distanceFieldVector, width);

    //something similiar to watershed segmentation algorithm
    SortSimpleVector<int> sortedDistanceField(distanceField.Data);
    int x,y;
    int x0,y0;
    int x1,y1;

    while (!sortedDistanceField.Empty())
    {
        int id = sortedDistanceField.PopIndexMax();
        if ( distanceField.Data[id] != 0)
        {
            distanceField.GetXY(id, &x, &y);
            
            distanceField.FillRect(x, y, bind2nd(std::not_equal_to<int>(), 0), &x0, &y0, &x1, &y1);

            distanceField.SetRegion(x0, y0, x1, y1, 0);

            AStar::Rectangle<CoordType> rect(
                Point<CoordType>( x0*_cellSize.X, y0*_cellSize.Y),
                Point<CoordType>( (x1+1)*_cellSize.X, (y1+1)*_cellSize.Y));
            result.push_back(rect);
        }
    }

    //for (int k = 0; k < height; k++)
    //{
    //    for (int i = 0; i < width; i++)
    //    {
    //        int id = k*width + i;
    //        printf("%2d",(int)distanceField[id]);
    //    }
    //    printf("\n");
    //}
    return result;
}

template<class CellType, typename CoordType>
AStar::Rectangle<int>
FieldNavRectMapView<CellType, CoordType>::
FillRect(int x,int y, std::vector<int>& distanceField, int width)
{
    int x0 = x;
    int y0 = y;
    int x1 = x;
    int y1 = y;
    AStar::Rectangle<int> rect;
    //bool x0free = Check(x0, y0-1, x1, y0-1, distanceField, width);
    //bool y0free = Check(x0-1, y0, x0-1, y1, distanceField, width);
    //bool xy0free = distanceField
    return rect;
}

#endif
