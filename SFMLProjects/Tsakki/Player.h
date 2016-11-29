#ifndef PLAYER_H
#define PLAYER_H

enum class COLOR
{
	WHITE,
	BLACK
};

enum class PLAYERTYPE
{
	LOCAL,
	INTERNET,
	AI,
};

enum class POSITION
{
	UP,
	DOWN
};

struct Player
{
	COLOR color;
	PLAYERTYPE type;
	POSITION position;
};

//#include "Move.h"
//
//#include <vector>
//
//class Player
//{
//public:
//	Player();
//	~Player();
//
//	std::vector<ChessPiece*> GetPieces();
//private:
//	std::vector<ChessPiece*> pieces;
//	std::vector<Move> moves;
//	//std::vector<
//	bool isCheckmate = false;
//	bool isCheck;
//};

#endif
