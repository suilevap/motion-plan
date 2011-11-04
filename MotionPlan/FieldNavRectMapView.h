#ifndef MOTIONPLAN_FIELDNAVRECTMAPVIEW_H_
#define MOTIONPLAN_FIELDNAVRECTMAPVIEW_H_

#include <vector>

#include "NavigationRectangle.h"
#include "NavRectMapView.h"
#include "GridMapView.h"
#include "Rectangle.h"
#include "SortSimpleVector.h"
#include "Vector2D.h"

template<class CellType, typename CoordType = float>
class FieldNavRectMapView: 
    public AStar::NavRectMapView<CellType, CoordType, true>
{
private:

protected:
    Point<CoordType> _cellSize;

    std::vector<AStar::Rectangle<CoordType>> LoadFrom(GridMapView<CellType, CoordType>* map, CoordType minRectSize);

    static AStar::Rectangle<int> FillRect(int x,int y, std::vector<int>& distanceField, int width);

    FieldNavRectMapView(){}

public:
    virtual ~FieldNavRectMapView(){}
    
    static FieldNavRectMapView<CellType, CoordType>* Create(GridMapView<CellType, CoordType>* fromMap);
    static FieldNavRectMapView<CellType, CoordType>* Create(GridMapView<CellType, CoordType>* fromMap, CoordType minRectSize);
};

#include "FieldNavRectMapView.inl"


#endif //MOTIONPLAN_FIELDNAVRECTMAPVIEW_H_