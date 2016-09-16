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
	ChessPiece(ChessPieceType const type, int const player);
	~ChessPiece();

	void GetTablePosition();
	void SetTablePosition();
	const char* GetChessPieceType();

	sf::Sprite GetSprite(){ return sprite; };

	int player;
	ChessPieceType type;
private:

	std::vector<int> tablePosition;
	sf::Texture texture;
	sf::Sprite sprite;

};

#endif
