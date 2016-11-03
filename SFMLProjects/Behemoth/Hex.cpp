#include "Hex.h"


Hex::Hex()
{
	hexagon = new sf::CircleShape(10, 6);
	hexagon->setFillColor(sf::Color::Green);
	hexagon->setOutlineColor(sf::Color::Yellow);
	hexagon->setOutlineThickness(2);
	hexagon->setOrigin(hexagon->getLocalBounds().width * 0.5f, hexagon->getLocalBounds().height * 0.5f);
}

Hex::~Hex()
{

}

void Hex::setTexture(HEXTYPE _type)
{
	switch (_type)
	{
	case DenseForest:
	{

	}
		break;
	case LightForest:
	{

	}
		break;
	case ClearGrass:
	{

	}
		break;
	default:
		break;
	}
}