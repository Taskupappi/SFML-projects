#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	 void GenerateNewMap(const unsigned int width, const unsigned int height, unsigned int fillPercentage);

private:
};

#endif
