#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <SFML\Graphics.hpp>

#include <list>
#include <vector>
#include <string>

enum ChessPieceType
{
	pawn,
	knight,
	rook,
	bishop,
	queen,
	king
};

class ChessPiece
{
public:
	ChessPiece(ChessPieceType const type, int const player, sf::Vector2u tablePosition);
	~ChessPiece();
	
	const char* GetChessPieceType();

	sf::Sprite& GetSprite(){ return sprite; };

	int player;
	bool hasMoved = false;
	ChessPieceType type;
	sf::Vector2u tablePosition;
	std::vector<sf::Vector2u> possibleMoves;
	std::vector<sf::Vector2u> allMoves;
private:
	sf::Sprite sprite;
	sf::Texture texture;


};

#endif
