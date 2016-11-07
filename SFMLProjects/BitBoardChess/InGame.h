#ifndef INGAME_H
#define INGAME_H

#include "Board.h"

int Sq120ToSq64[BOARD_SQUARE_NUMBER];
int Sq64ToSq120[64];

class InGame
{
public:
	InGame();
	~InGame();

	bool Init();
private:
	Board board;
};

#endif