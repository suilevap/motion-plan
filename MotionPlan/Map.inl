#ifndef MOTIONPLAN_MAP_H_
#error "Include from Map.h only."
#else

template<class CellType>
inline int Map<CellType>::GetBorder()
{
	return _border;
}

template<class CellType>
void Map<CellType>::InitMap(int width, int height, int border)
{
	_border = border;
	_width = width + _border * 2;
	_height = height + _border * 2;
	int size = _width*_height;
	_map = new CellType[size];
	memset(_map, 0, sizeof(_map[0])*size);
}

template<class CellType>
Map<CellType>::Map(int width, int height)
{
	InitMap(width, height, 1);
}

template<class CellType>
Map<CellType>::Map(int width, int height, int border)
{
	InitMap(width, height, border);
}

template<class CellType>
Map<CellType>::Map(Map<CellType>* map)		
{
	InitMap(map->GetWidth(), map->GetHeight(), map->GetBorder());
}

template<class CellType>
Map<CellType>::~Map(void)
{
	delete[] _map;
}

template<class CellType>
Point Map<CellType>::GetCellPoint(int index)
{
	Point p;
	p.X = index % _width - _border;
	p.Y = index / _width - _border;
	return p;
}

template<class CellType>
inline void Map<CellType>::GetD(int index1, int index2, int* dx, int* dy)
{
	*dx = (index2 % _width) - (index1 % _width );
	*dy = (index2 / _width) - (index1 / _width) ;
}

template<class CellType>
inline float Map<CellType>::GetEvclDist(int p1, int p2)
{
	float result;
	
	int x1 = p1 % _width;
	int y1 = p1 / _width;
	int x2 = p2 % _width;
	int y2 = p2 / _width;
	result = DistanceEvaluator::EuclideanDistance(x1, y1, x2, y2);//DistanceEvaluator::EuclideanDistance(x1, y1, x2, y2);
	return result;
}

template<class CellType>
int Map<CellType>::GetCellIndex(int x, int y)
{
	return (x + _border) + (y + _border) * _width ;
}

template<class CellType>
inline int Map<CellType>::GetCellIndex(int index, int dx, int dy)
{
	return index + dy * _width + dx ;
}

template<class CellType>
inline CellType Map<CellType>::GetCell(int index)
{
	return _map[index] ;
}

template<class CellType>
inline CellType Map<CellType>::GetCell(int x, int y)
{
	return _map[GetCellIndex(x,y)];
}

template<class CellType>
inline void Map<CellType>::SetCell(int index, CellType cell)
{
	_map[index] = cell;
}

template<class CellType>
inline void Map<CellType>::SetCell(int x, int y, CellType cell)
{
	SetCell(GetCellIndex(x,y), cell);
}

template<class CellType>
void Map<CellType>::SetCellRegion(int x, int y, CellType cell, int width, int height)
{
	for ( x= x; x<x+width; x++)
	{
		for ( y= y; y<y+height; y++)
		{
			_map[GetCellIndex(x,y)] = cell;
		}
	}
}

template<class CellType>
inline int Map<CellType>::GetWidth()
{
	return _width - _border * 2;
}

template<class CellType>
int Map<CellType>::GetHeight()
{
	return _height - _border * 2;
}

template<class CellType>
void Map<CellType>::ToOutput()
{
	int w = GetWidth();
	int h = GetHeight();
	for (int k = 0; k < h; k++)
	{
		for (int i =0; i < w; i++)
		{
			//printf("%3d",(int)( (int)(GetCell(i , k)*10 )%100 ));
			printf("%3d",(int)GetCell(i , k));
		}
		printf("\n");
	}
	printf("========================\n");
}

template<class CellType>
void Map<CellType>::ToOutputField()
{
	const char * presentation = "\\|/-.-/|\\";
	int w = GetWidth();
	int h = GetHeight();
	for (int k = 0; k < h; k++)
	{
		for (int i =0; i < w; i++)
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

template<class CellType>
Map<int>* Map<CellType>::LoadFrom(std::string &data, std::vector<Point>* specialPoints)
{
	int width = data.find("\r\n");
	int height = (data.length()+2) / (width + 2);
	Map<int>* map = new Map<int>(width, height);
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
				cell = 0;
			}
			else
			{
				cell = 1;
			}
			if ((symbol>='0') && (symbol<='9'))
			{
				int idx = (int)(symbol-'0');
				Point point;
				point.X = i;
				point.Y = k;
				(*specialPoints)[idx]=point;
			}
			map->SetCell(i,k, cell);
			index++;
		}
		index+=2;
	}

	return map;
}

#endif
