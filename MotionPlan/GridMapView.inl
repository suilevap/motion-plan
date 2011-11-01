#ifndef MOTIONPLAN_GRIDMAPVIEW_H_
#error "Include from GridMapView.h only."
#else

#include "DistanceEvaluator.h"
#include "MathConstants.h"

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::GetNeighbors(int node, FastVector<AStar::EdgeInfo<int,float>>& neighbors)
{
    neighbors.clear();
	neighbors.resize(8);

	static float step1 = 1 * _cellSize.X;//_cellSize.X;
	static float stepD = SQRT_2 * _cellSize.X;//_cellSize.X * SQRT_2;
    AddNeighbor( GetNodeDxDy(node, 1, 0) , step1, neighbors);
    AddNeighbor( GetNodeDxDy(node, - 1, 0) , step1, neighbors);
    AddNeighbor( GetNodeDxDy(node, 0, 1) , step1, neighbors);
    AddNeighbor( GetNodeDxDy(node, 0, -1) , step1, neighbors);

    AddNeighbor( GetNodeDxDy(node, 1, 1), stepD, neighbors);
    AddNeighbor( GetNodeDxDy(node, 1, -1), stepD, neighbors);
    AddNeighbor( GetNodeDxDy(node, -1, 1), stepD, neighbors);
    AddNeighbor( GetNodeDxDy(node, -1, -1), stepD, neighbors);
	
}

template<class CellType, typename CoordType>
inline void GridMapView<CellType, CoordType>::AddNeighbor(int node, float d, FastVector<AStar::EdgeInfo<int,float>>& neighbors)
{
    if (GetCell(node) != ObstacleCellValue)	
    {
        neighbors.push_back(AStar::EdgeInfo<int,float>(node, d));
    }
}


template<class CellType, typename CoordType>
inline void GridMapView<CellType, CoordType>::TransformPointToCell(Point<CoordType>& pointFrom, Point<int>& pointTo)
{
	pointTo.X = static_cast<int>(pointFrom.X * _scale.X );
	pointTo.Y = static_cast<int>(pointFrom.Y * _scale.Y );	
}
template<class CellType, typename CoordType>
inline void GridMapView<CellType, CoordType>::TransformPointToWorld(Point<int>& pointFrom, Point<CoordType>& pointTo)
{
	pointTo.X = static_cast<CoordType>((pointFrom.X + 0.5) * _cellSize.X );
	pointTo.Y = static_cast<CoordType>((pointFrom.Y + 0.5) * _cellSize.Y );
}

template<class CellType, typename CoordType>
inline Point<int> GridMapView<CellType, CoordType>::GetMapPoint(int node)
{
	Point<int> pointMap;
	pointMap.X = node % _width - _border;
	pointMap.Y = node / _width - _border;
	return pointMap;
}
template<class CellType, typename CoordType>
inline int GridMapView<CellType, CoordType>:: GetNodeFromMapPoint(const Point<int>& pointMap)
{
	return (pointMap.X + _border) + (pointMap.Y + _border) * _width ;
}

template<class CellType, typename CoordType>
inline int GridMapView<CellType, CoordType>::GetNodeDxDy(int node, int dx, int dy)
{
    return node + dx + dy * _width;
}

template<class CellType, typename CoordType>
Point<CoordType> GridMapView<CellType, CoordType>::GetPoint(int node)
{
	Point<CoordType> pointWorld;
	Point<int> pointMap = GetMapPoint(node);

	TransformPointToWorld(pointMap, pointWorld );
	return pointWorld;
}
template<class CellType, typename CoordType>
float GridMapView<CellType, CoordType>::GetCost(Point<CoordType>& p1,Point<CoordType>& p2)
{
	float cost = AStar::DistanceEvaluator::DiagonalDistance<float>(p1, p2);
	return cost;
}

template<class CellType, typename CoordType>
int GridMapView<CellType, CoordType>::GetNode(Point<CoordType>& pointWorld)
{
	Point<int >pointMap;
	TransformPointToCell(pointWorld, pointMap);
	return GetNodeFromMapPoint(pointMap);
}


template<class CellType, typename CoordType>
Point<CoordType> GridMapView<CellType, CoordType>::GetMaxPoint()
{
	Point<int> p;
	p.X = _width - _border * 2 - 1;
	p.Y = _height - _border * 2 - 1;
	Point<CoordType> result;
	TransformPointToWorld(p, result);
	result.X += _cellSize.X / 2;
	result.Y += _cellSize.Y / 2;

	return result;
}

template<class CellType, typename CoordType>
bool GridMapView<CellType, CoordType>::OnMap(Point<CoordType>& point)
{
	Point<CoordType> maxPoint = GetMaxPoint();
	return ((point.X >= 0) &&(point.Y >= 0)&&(point.X < maxPoint.X)&&(point.Y < maxPoint.Y));
}

template<class CellType, typename CoordType>
int GridMapView<CellType, CoordType>::GetMaxNode()
{
	return _width * _height;
}

template<class CellType, typename CoordType>
inline int GridMapView<CellType, CoordType>::GetBorder()
{
	return _border;
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::InitMap(CoordType width, CoordType height, int border, Point<CoordType> cellSize)
{

    _distanceField = NULL;

	_cellSize = cellSize;
	_scale = Point<float>(1.0f / _cellSize.X, 1.0f / _cellSize.Y);

	Point<int> mapSize;
	Point<CoordType> dataSize(width, height);
	TransformPointToCell(dataSize, mapSize);

	_border = border;
	_width = mapSize.X + _border * 2;
	_height = mapSize.Y + _border * 2;
	int size = _width * _height;
	//_map = new CellType[size];
    _map.resize(size);
	Clear( FreeCellValue, ObstacleCellValue);

}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::GridMapView(CoordType width, CoordType height)
:ObstacleCellValue(1),FreeCellValue(0)
{
	InitMap(width, height, 1, Point<CoordType>(1,1));
}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::GridMapView(CoordType width, CoordType height, CoordType cellWidth)
:ObstacleCellValue(1),FreeCellValue(0)
{
	InitMap(width, height, 1, Point<CoordType>(cellWidth, cellWidth));
}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::GridMapView()
:ObstacleCellValue(1),FreeCellValue(0)
{
	
}

//template<class CellType, typename CoordType>
//GridMapView<CellType, CoordType>::GridMapView(int width, int height, int border)
//{
//	InitMap(width, height, border);
//}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::~GridMapView(void)
{
	//delete[] _map;
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::SetCellRegion(Point<CoordType>& point, CellType cell, Point<CoordType>& size)
{

	for (float i = point.X; i < (point.X + size.X); i += _cellSize.X/2)
	{
		for (float k = point.Y; k < (point.Y + size.Y); k += _cellSize.Y/2)
		{
			Point<CoordType> curPoint(i,k);
			int node = GetNodeWrite(curPoint);
			SetCell(node, cell);
		}
	}
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::Clear(CellType value, CellType valueBorder)
{
	int size = _width*_height;
    _map.assign(size, value);
	if (value != valueBorder)
	{
		for (int i = 0; i < _height; ++i)
		{
			for (int k = 0; k < _border; ++k)
			{
				//TODO: use SetCell
				_map[i * _width + k] = valueBorder;
				_map[i * _width + _width - k - 1] = valueBorder;
			}
		}
		for (int k = _border; k < _width - _border; ++k)
		{
			for (int i = 0; i < _border; ++i)
			{
				//TODO: use SetCell
				_map[i * _width + k] = valueBorder;
				_map[(_height - i - 1) * _width + k] = valueBorder;
			}
		}

	}
}

template<class CellType, typename CoordType>
bool GridMapView<CellType, CoordType>::
IsCellRegionIsotropic(Point<CoordType>& point1, Point<CoordType>& point2, CellType* cell)
{
    bool result;
    CellType baseCell = GetCellPoint(point1);
    CellType currentCell;
    Point<CoordType> cellSize = GetCellSize();
	for (float i = point1.X; i < point2.X; i += cellSize.X/2)
	{
		for (float k = point1.Y; k < point2.Y; k += cellSize.Y/2)
		{
			Point<CoordType> curPoint(i,k);
			currentCell = GetCellPoint(curPoint);
			if (currentCell != baseCell)
            {
                //TODO: several return - bad
                return false;
            }
		}
	}
    *cell = baseCell;
    return true;
}

template<class CellType, typename CoordType>
GridMapView<float, CoordType>* GridMapView<CellType, CoordType>::
GetDistanceField()
{
    //TODO: thread unsafe
    if (_distanceField == NULL)
    {
        CreateDistanceField();
    }
    return _distanceField;
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::
CreateDistanceField()
{
    Point<CoordType> size = GetMaxPoint();
    GridMapView<float, CoordType>* result = new GridMapView<float, CoordType>(
        size.X, size.Y, _cellSize.X);

    float width = size.X;
    float height = size.Y;
    Point<CoordType> fieldCellSize = result->GetCellSize();
    //generate distance field
    //pass 1
	for (float k = 0; k < height; k += fieldCellSize.Y)
	{
	    for (float i = 0; i < width; i += fieldCellSize.X)
		{
            Point<CoordType> point(i, k);
            int id = result->GetNode(point);
            int value;
            if (GetCellPoint(point) == GridMapView<CellType, CoordType>::FreeCellValue)
            {
                //border
                if(k>0 && k<height-fieldCellSize.Y && i>0 && i<width-fieldCellSize.X)
                {
                    value = min(
                                min(
                                    result->GetCell(result->GetNodeDxDy(id, -1, 0)), 
                                    result->GetCell(result->GetNodeDxDy(id, 0, -1)))
                                +1,
                                min(
                                    result->GetCell(result->GetNodeDxDy(id, -1, -1)), 
                                    result->GetCell(result->GetNodeDxDy(id, 1, -1)))
                                +SQRT_2
                            );
                }
                else
                {
                    value = 1;
                }
            }
            else
            {
                value = 0;
            }
            result->SetCell(id, value);

        }
    }
    //pass 2
    for (float k = height-fieldCellSize.Y/2; k >= 0; k -= fieldCellSize.Y)
    {
        for (float i = width-fieldCellSize.X/2; i >= 0; i -= fieldCellSize.X)
        {
            Point<CoordType> point(i, k);
            int id = result->GetNode(point);
            int value;
            if (GetCellPoint(point) == GridMapView<CellType, CoordType>::FreeCellValue)
            {
                //border
                if(k>0 && k<height-fieldCellSize.Y && i>0 && i<width-fieldCellSize.X)
                {
                    value = min(
                                min(
                                    result->GetCell(result->GetNodeDxDy(id, 1, 0)), 
                                    result->GetCell(result->GetNodeDxDy(id, 0, 1)))
                                +1,
                                min(
                                    result->GetCell(result->GetNodeDxDy(id, 1, 1)), 
                                    result->GetCell(result->GetNodeDxDy(id, -1, 1)))
                                +SQRT_2
                            );
                    value = min(value, result->GetCell(id));
                }
                else
                {
                    value = 1;
                }
            }
            else
            {
                value = 0;
            }
            result->SetCell(id, value);
        }
    }
    ////blur
    //for (int k = height-fieldCellSize.Y; k > fieldCellSize.Y; k -= fieldCellSize.Y)
    //{
    //    for (int i = width-fieldCellSize.X; i > fieldCellSize.X; i -= fieldCellSize.X)
    //    {
    //        Point<CoordType> point(i, k);
    //        float
    //        result->SetCellPoint(point
    //    }
    //}

    //TODO: thread unsafe
    if (_distanceField != NULL)
    {
        delete _distanceField;
    }
    _distanceField = result;
}

template<class CellType, typename CoordType>
int GridMapView<CellType, CoordType>::
ToVector(std::vector<CellType>* data)
{
    Point<CoordType> size = GetMaxPoint();
    int width = static_cast<int>(size.X /_cellSize.X);
    int height = static_cast<int>(size.Y / _cellSize.Y);
    data->resize(width*height);
	for (int k = 0; k < height; k++)
	{
	    for (int i = 0; i < width; i++)
		{
            Point<CoordType> point(i * _cellSize.X, k * _cellSize.Y);
            int id = k*width + i;
            (*data)[id] = GetCellPoint(point);
        }
    } 
    return width;
}


//only for test!!
template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::ToOutput()
{
	Point<CoordType> size = GetMaxPoint();

	float w = size.X;
	float h = size.Y;
	for (float k = 0; k < h; k += _cellSize.Y)
	{
		for (float i =0; i < w; i += _cellSize.X)
		{
			//printf("%3d",(int)( (int)(GetCell(i , k)*10 )%100 ));
			Point<CoordType> point(i , k);
			printf("%2d",(int)GetCellPoint(point));
		}
		printf("\n");
	}
	printf("========================\n");
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::ToOutputField()
{
	const char * presentation = "\\|/-.-/|\\";
	Point<CoordType> size = GetMaxPoint();

	int w = size.X;
	int h = size.Y;
	for (int k = 0; k < h; k += _cellSize.Y)
	{
		for (int i =0; i < w; i += _cellSize.X)
		{
			int dx;
			int dy;
			int ind1 = (int)GetCell(i , k);
			int ind2 = GetCellIndex(i, k);
			GetD(ind1, ind2, &dx, &dy);
			char s;
			if (ind1 != 0)
			{
				s = presentation[(dx+1)+(dy+1)*3];
			}
			else
			{
				s = '.';
			}
			printf("%c", s);
			//printf("%3d",(dx+1)*10+(dy+1));
		}
		printf("\n");
	}
	printf("========================\n");
}

template<class CellType, typename CoordType>
GridMapView<int>* GridMapView<CellType, CoordType>::LoadFrom(std::string &data, std::vector<Point<CoordType>>* specialPoints)
{
	int width = data.find("\r\n");
	int height = (data.length()+2) / (width + 2);
	GridMapView<int>* map = new GridMapView<int>(width, height);
	specialPoints->resize(10);
	int index = 0;
	int cell;
	for (int k = 0; k < height; k++)
	{
		for (int i = 0; i < width; i++)
		{
			char symbol=data[index];
			if (symbol =='#')
			{
				cell = ObstacleCellValue;
			}
			else
			{
				cell = 0;
			}
			if ((symbol>='0') && (symbol<='9'))
			{
				int idx = (int)(symbol-'0');
				Point<CoordType> point(i, k);
				
				(*specialPoints)[idx]=point;
			}
			map->SetCellPoint(Point<CoordType>(i,k), cell);
			index++;
		}
		index+=2;
	}

	return map;
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::LoadFromVector(const std::vector<CellType>& data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		SetCell(i, data[i]);
	}
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::LoadFromVector2D(Vector2D<CellType>& data)
{
    int width = data.Width;
    int height = data.Height;

	for (int x = 0; x < width; ++x)
    {
	    for (int y = 0; y < height; ++y)
	    {
            int node = GetNodeFromMapPoint(Point<int>(x, y));
            CellType value= data.GetData(x,y);
		    SetCell(node, value);
	    }
    }
}

#endif
