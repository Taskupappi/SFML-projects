#ifndef HEX_H
#define HEX_H

#include "SFML\Graphics.hpp"

class Hex : public sf::Drawable, public sf::Transformable
{
public:
	Hex(const int size);
	~Hex();

private:
	sf::CircleShape* hexagon;

};

#endif
