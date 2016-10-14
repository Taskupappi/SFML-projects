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
	ChessPiece(ChessPieceType const type, int const player, sf::Vector2i tablePosition);
	~ChessPiece();
	
	const char* GetChessPieceType();

	sf::Sprite& GetSprite(){ return sprite; };

	int player;
	bool hasMoved = false;
	ChessPieceType type;
	sf::Vector2i tablePosition;
	std::vector<sf::Vector2i> possibleMoves;
	std::vector<sf::Vector2i> allMoves;
private:
	sf::Sprite sprite;
	sf::Texture texture;


};

#endif
