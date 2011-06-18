#pragma once

#include <stack>
#include <vector>
#include <string>
#include "Point.h"


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

public:
	//Map(int width, int height);
	//~Map(void);

	//CellType GetCell(int x, int y);

	//void SetCell(int x, int y, CellType cell);
	//void SetCellRegion(int x, int y, CellType cell, int width, int height);
	//void SetCellRhomb(int x, int y, CellType cell, int r);
	//int GetWidth();
	//int GetHeight();

	inline Point GetCellPoint(int index)
	{
		Point p;
		p.X = index / _width;
		p.Y = index % _width;
		return p;
	}


	inline int GetCellIndex(int x, int y)
	{
		return (x + _border) * _width + (y + _border) ;
	}

	inline int GetCellIndex(int index, int dx, int dy)
	{
		return index + dx*_width + dy ;
	}

	inline CellType GetCell(int index)
	{
		return _map[index] ;
	}

	Map(int width, int height, int border)
	{
		_border = border;
		_width = width + _border * 2;
		_height = height + _border * 2;
		_map = new CellType[_width*_height];
	}

	Map(Map<CellType>* map)
		:this(map->GetWidth(), map->GetHeight(), map->GetBorder())
	{
		/*_border = map->GetBorder();
		_width =  map->GetWidth() + _border * 2;
		_height = map->GetHeight() + _border * 2;
		_map = new CellType[_width*_height];*/
	}

	Map(int width, int height)
	{
		_border = 1;
		_width = width;
		_height = height;
		_map = new CellType[_width*_height];
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

		for (int i =0; i < w; i++)
		{
			for (int k = 0; k < h; k++)
			{
				printf("%d",GetCell(i , k));
			}
			printf("\n");
		}
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
