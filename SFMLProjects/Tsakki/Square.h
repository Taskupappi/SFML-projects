#ifndef SQUARE_H
#define SQUARE_H

#include <SFML\Graphics.hpp>

class Square
{
public:
	Square(bool isWhite);
	~Square();
private:
	sf::Sprite sprite;
	sf::Texture texture;
	bool isWhite;
};

#endif