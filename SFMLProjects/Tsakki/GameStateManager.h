#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <list>
#include "InGame.h"


class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void AddState(GameState* state);
	void PopState();
	

private:
	std::list<GameState*> states;

};

#endif