#ifndef SQUARE_H
#define SQUARE_H

#include <SFML\Graphics.hpp>

class Square
{
public:
	Square(bool isWhite);
	~Square();

	sf::Sprite sprite;
	bool isWhite;
private:

	sf::Texture texture;

};

#endif