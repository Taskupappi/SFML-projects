#ifndef SQUARE_H
#define SQUARE_H

#include <SFML\Graphics.hpp>

class Square
{
public:
	Square(bool isWhite, const unsigned int tablePosX, const unsigned int tablePosY);
	~Square();

	sf::Sprite sprite;
	bool isWhite;
	const sf::Vector2u tablePosition;
private:

	sf::Texture texture;
};

#endif