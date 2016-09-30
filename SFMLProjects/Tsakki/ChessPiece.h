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

	//void GetTablePosition();
	// void SetTablePosition();
	const char* GetChessPieceType();

	sf::Sprite& GetSprite(){ return sprite; };

	int player;
	ChessPieceType type;
	sf::Vector2i tablePosition;
private:
	sf::Sprite sprite;
	sf::Texture texture;
};

#endif
