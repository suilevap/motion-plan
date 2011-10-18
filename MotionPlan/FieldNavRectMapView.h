#ifndef MOTIONPLAN_FIELDNAVRECTMAPVIEW_H_
#define MOTIONPLAN_FIELDNAVRECTMAPVIEW_H_

#include <vector>

#include "NavigationRectangle.h"
#include "NavRectMapView.h"
#include "GridMapView.h"
#include "Rectangle.h"

template<class CellType, typename CoordType = float>
class FieldNavRectMapView: 
    public AStar::NavRectMapView<CellType, CoordType>
{
private:

protected:
    Point<CoordType> _cellSize;

    std::vector<AStar::Rectangle<CoordType>> LoadFrom(GridMapView<CellType, CoordType>* map);

    FieldNavRectMapView(){}

public:
    virtual ~FieldNavRectMapView(){}
    
    static FieldNavRectMapView<CellType, CoordType>* Create(GridMapView<CellType, CoordType>* fromMap);
};

#include "FieldNavRectMapView.inl"


#endif //MOTIONPLAN_FIELDNAVRECTMAPVIEW_H_