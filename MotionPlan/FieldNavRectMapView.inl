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

    Point<CoordType> size = map->GetMaxPoint();
    int width = static_cast<int>(size.X /_cellSize.X);
    int height = static_cast<int>(size.Y / _cellSize.Y);

    int* distanceField = new int[width * height];
    //generate distance field
    //pass 1
	for (int k = 0; k < height; k++)
	{
	    for (int i = 0; i < width; i++)
		{
            int id = k*width + i;
            Point<CoordType> point(i * _cellSize.X, k * _cellSize.Y);
            if (map->GetCellPoint(point) == GridMapView<CellType, CoordType>::FreeCellValue)
            {
                //border
                if(k>0 && k<height-1 && i>0 && i<width-1)
                {
                    distanceField[id] = min(
                            min(distanceField[id-1], distanceField[id-width]),
                            min(distanceField[id-1-width],distanceField[id+1-width])
                        )+1;
                }
                else
                {
                    distanceField[id] = 1;
                }
            }
            else
            {
                distanceField[id] = 0;
            }
        }
    }
    //pass 2
    for (int k = height-1; k >= 0; k--)
    {
        for (int i = width-1; i >= 0; i--)
        {
            int id = k * width + i;
            Point<CoordType> point(i * _cellSize.X, k * _cellSize.Y);
            if (map->GetCellPoint(point) == GridMapView<CellType, CoordType>::FreeCellValue)
            {
                if(k>0 && k<height-1 && i>0 && i<width-1)
                {
                    distanceField[id] = 
                        min(distanceField[id],
                            min(
                                min(distanceField[id+1], distanceField[id+width]), 
                                min(distanceField[id+1+width], distanceField[id-1+width])
                            )+1
                        );
                }
                else
                {
                    distanceField[id] = 1;
                }
            }
            else
            {
                distanceField[id] = 0;
            }
        }
    }

    for (int k = 0; k < height; k++)
	{
	    for (int i = 0; i < width; i++)
		{
            int id = k*width + i;
			printf("%2d",(int)distanceField[id]);
        }
		printf("\n");

    }
    delete[] distanceField;
    return result;
}

#endif
