#include "Square.h"

Square::Square( bool _isWhite)
{
	isWhite = _isWhite;

	texture.loadFromFile("ChessboardSquares.png");
	sprite.setTexture(texture);

	if (isWhite)
	{
		sprite.setTextureRect(sf::IntRect(10, 0, 10, 10));
	}
	else
	{
		sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
	}

	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setScale(5.0f, 5.0f);
}

Square::~Square()
{

}