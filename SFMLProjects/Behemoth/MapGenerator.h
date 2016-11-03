#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

#include "Map.h"

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	 void GenerateNewMap(const unsigned int width, const unsigned int height, unsigned int fillPercentage);

private:
	std::vector<Map*> maps;
};

#endif
