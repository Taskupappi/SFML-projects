#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <SFML\Graphics.hpp>

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
	ChessPiece(ChessPieceType const type, bool player1);
	~ChessPiece();

	void GetTablePosition();
	void SetTablePosition();


private:

	std::vector<int> tablePosition;
	sf::Texture texture;
	sf::Sprite sprite;
	bool player1;
};

#endif