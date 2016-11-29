#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <SFML\Graphics.hpp>

#include <list>
#include <vector>
#include <string>

#include "Player.h"

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
	ChessPiece(ChessPieceType const type, Player const player);
	~ChessPiece();

	const char* GetChessPieceType();

	sf::Sprite& GetSprite(){ return sprite; };

	Player player;
	ChessPieceType type;
	sf::Vector2i tablePosition;
	sf::Vector2i lastPosition;
	std::vector<sf::Vector2i> possibleMoves;

	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> allMoves;

	std::vector<sf::Vector2i> checkingMoves;
	bool isChecking = false;
private:
	sf::Sprite sprite;
	sf::Texture texture;


};

#endif
