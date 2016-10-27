#ifndef HEX_H
#define HEX_H

#include "SFML\Graphics.hpp"

class Hex : public sf::Transformable
{
public:
	Hex();
	~Hex();

private:
	sf::CircleShape* hexagon;

};

#endif
