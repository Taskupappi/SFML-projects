#include "Map.h"

Map::Map(const unsigned int width, const unsigned int height)
{
	//set map size
	hexes = new Hex*[height];
	for (size_t i = 0; i < width; i++)
	{
		hexes[i] = new Hex[width];
	}
}

void Map::InsertHexToMap(Hex* _mapHex, const unsigned int _positionX, const unsigned int _positionY)
{
	hexes[_positionX][_positionY] = _mapHex;
}