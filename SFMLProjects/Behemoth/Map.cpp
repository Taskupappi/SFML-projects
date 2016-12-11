#include "Map.h"

Map::Map(const unsigned int _width, const unsigned int _height)
	:mapWidth(_width)
{
	//set map size
	hexes = new Hex[_width * _height];

	//fill with hexes
	for (int x = 0; x <_width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			Hex* hex = new Hex();
			SetHex(hex, x, y);
		}
	}

	//set hexes on correct positions
}

//void Map::InsertHexToMap(Hex* _mapHex, const unsigned int _positionX, const unsigned int _positionY)
//{
//	hexes[_positionX][_positionY] = _mapHex;
//}

Hex* Map::GetHex(const int x, const int y)
{

	return &hexes[x + mapWidth * y];
	//return hexes[x + mapWidth * y];
}

void Map::SetHex(Hex* _mapHex, const int x, const int y)
{
	hexes[x + mapWidth * y] = *_mapHex;
	hexes[x + mapWidth * y].setPosition(hexes[0].GetShape()->getLocalBounds().width * 0.5f, hexes[0].GetShape()->getLocalBounds().height * 0.5f);
}