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

    std::vector<int> distanceField;
    int width = distanceFieldMap->ToVector(&distanceField);
    int height = distanceField.size() / width;
    

    for (int k = 0; k < height; k++)
    {
        for (int i = 0; i < width; i++)
        {
            int id = k*width + i;
            printf("%2d",(int)distanceField[id]);
        }
        printf("\n");
    }
    return result;
}

#endif
