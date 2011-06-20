#pragma once

#include <stack>
#include <vector>
#include <string>
#include "Point.h"
#include "DistanceEvaluator.h"


//typedef float CellType;

template<class CellType>
class Map
{
private:
	CellType* _map;
	int _width;
	int _height;
	int _border;
	//int GetCellIndex(int x, int y);

protected:
	inline int GetBorder()
	{
		return _border;
	}
	void InitMap(int width, int height, int border)
	{
		_border = border;
		_width = width + _border * 2;
		_height = height + _border * 2;
		int size = _width*_height;
		_map = new CellType[size];
		memset(_map, 0, sizeof(_map[0])*size);
	}

public:
	Map(int width, int height)
	{
		InitMap(width, height, 1);
	}

	Map(int width, int height, int border)
	{
		InitMap(width, height, border);
	}

	Map(Map<CellType>* map)		
	{
		InitMap(map->GetWidth(), map->GetHeight(), map->GetBorder());
	}

	inline Point GetCellPoint(int index)
	{
		Point p;
		p.X = index % _width - _border;
		p.Y = index / _width - _border;
		return p;
	}

	inline float GetEvclDist(int p1, int p2)
	{
		float result;
		
		int x1 = p1 % _width;
		int y1 = p1 / _width;
		int x2 = p2 % _width;
		int y2 = p2 / _width;
		result = DistanceEvaluator::EuclideanDistance(x1, y1, x2, y2);//DistanceEvaluator::EuclideanDistance(x1, y1, x2, y2);
		return result;
	}


	inline int GetCellIndex(int x, int y)
	{
		return (x + _border) + (y + _border) * _width ;
	}

	inline int GetCellIndex(int index, int dx, int dy)
	{
		return index + dy * _width + dx ;
	}

	inline CellType GetCell(int index)
	{
		return _map[index] ;
	}

	~Map(void)
	{
		delete[] _map;
	}

	inline CellType GetCell(int x, int y)
	{
		return _map[GetCellIndex(x,y)];
	}

	inline void SetCell(int index, CellType cell)
	{
		_map[index] = cell;
	}

	inline void SetCell(int x, int y, CellType cell)
	{
		SetCell(GetCellIndex(x,y), cell);
	}

	void SetCellRegion(int x, int y, CellType cell, int width, int height)
	{
		for ( x= x; x<x+width; x++)
		{
			for ( y= y; y<y+height; y++)
			{
				_map[GetCellIndex(x,y)] = cell;
			}
		}
	}

	void SetCellRhomb(int x, int y, CellType cell, int r)
	{
		/*for (int k=-r; k < r; k++)
		{
			for (int i = r-abs(k); i,)
		}*/
	}

	inline int GetWidth()
	{
		return _width - _border * 2;
	}

	int GetHeight()
	{
		return _height - _border * 2;
	}

	void ToOutput()
	{
		int w = GetWidth();
		int h = GetHeight();
		for (int k = 0; k < h; k++)
		{
			for (int i =0; i < w; i++)
			{
				printf("%3d",(int)GetCell(i , k));
			}
			printf("\n");
		}
		printf("========================\n");
	}

	static Map<int>* LoadFrom(std::string &data, std::vector<Point>* specialPoints)
	{
		
		int width = data.find("\r\n");
		int height = (data.length()+2) / (width + 2);
		Map<int>* map = new Map<int>(width, height, 1);
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
				/*if (data[index] =='0')
				{
					Point point;
					point.X = i;
					point.Y = i;
					specialPoints->
				}
				if (data[index] =='1')
				{
					Point point;
					point.X = i;
					point.Y = i;
					specialPoints->insert(1,point);
				}*/

				map->SetCell(i,k, cell);
				index++;
			}
			index+=2;
		}

		return map;
	}
};
