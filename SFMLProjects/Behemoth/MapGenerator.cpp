#include "MapGenerator.h"

MapGenerator::MapGenerator()
{

}

MapGenerator::~MapGenerator()
{

}

void MapGenerator::GenerateNewMap(const unsigned int _width, const unsigned int _height, unsigned int fillPercentage)
{
	std::srand(std::time(0));
	int random = std::rand();

	//Map* map = new Map();
	//maps.push_back(map);
}