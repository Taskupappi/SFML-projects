#include "Map.h"

Map::Map(const unsigned int width, const unsigned int height)
	:mapWidth(width)
{
	//set map size
	hexes = new Hex[width * height];
}

void Map::InsertHexToMap(Hex* _mapHex, const unsigned int _positionX, const unsigned int _positionY)
{
	hexes[_positionX][_positionY] = _mapHex;
}

Hex* Map::GetHexIndex(const int x, const int y)
{

	Hex* kisse = hexes[x + mapWidth * y];
	//return hexes[x + mapWidth * y];
}