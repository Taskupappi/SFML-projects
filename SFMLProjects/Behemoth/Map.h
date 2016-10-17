#ifndef MAP_H
#define MAP_H

#include "Hex.h"

class Map
{
	//class MapMatrix
	//{
	//public:
	//	MapMatrix(const unsigned int _width, const unsigned int _height)
	//		:width(_width), hexes(new Hex[_width * _height])
	//	{
	//	}

	//	~MapMatrix()
	//	{
	//		delete[] hexes;
	//	}

	//	Hex* at(unsigned int _x, unsigned int _y) const 
	//	{
	//		return hexes[index(_x, _y)]
	//	}

	//protected:
	//	Hex* index(unsigned int _x, unsigned int _y) const
	//	{
	//		return _x + width * _y;
	//	}
	//private:
	//	Hex* hexes;
	//	int width;
	//};


public:
	Map(const unsigned int width, const unsigned int height);
	Map();

	void InsertHexToMap(Hex* mapHex, const unsigned int positionX, const unsigned int positionY);

private:
	Hex** hexes;
};

#endif

class Matrix 
{ 
	int* array;
	int m_width;
	public:
	Matrix(int w, int h) : m_width(w), array(new int[w * h]) {}
	~Matrix() { delete[] array; }
	int at(int x, int y) const { return array[index(x, y)]; }
	protected:
	int index(int x, int y) const { return x + m_width * y; } 
};
