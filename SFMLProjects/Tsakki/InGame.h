#ifndef INGAME_H
#define INGAME_H

#include "GameState.h"

class InGame : public GameState
{
public:
	InGame(){};
	~InGame(){};

	void HandleTurn();
	void EndTurn();

	bool HandleInput();
	bool Move();

	void Draw();

private:

};
#endif

