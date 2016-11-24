#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <list>
//#include "InGame.h"

class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void AddState(GameState* state);
	void PopState();
	GameState* GetState(){ return states.front(); };
	
	void Initialize();
	void Uninitialize();

private:
	std::list<GameState*> states;

};

#endif
