#ifndef MAP_H
#define MAP_H

#include "Hex.h"



class Map
{
public:
	Map(const unsigned int width, const unsigned int height);
	Map();

	void InsertHexToMap(Hex* mapHex, const unsigned int positionX, const unsigned int positionY);
	Hex* GetHex(const int x, const int y);
	void SetHex(Hex* mapHex, const int x, const int y);
private:
	Hex* hexes;
	const int mapWidth;
};

#endif
