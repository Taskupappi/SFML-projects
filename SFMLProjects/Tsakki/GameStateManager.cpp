#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
	states.push_back((GameState*)(new InGame()));

	printf("kisse");
}

GameStateManager::~GameStateManager()
{
	std::list<GameState*>::iterator state = states.end();

	for (state = states.end(); state != states.begin(); --state)
	{
		delete (*state);
	}
}

void GameStateManager::AddState(GameState* _state)
{
	states.push_back(_state);
}

void GameStateManager::PopState()
{
	states.pop_front();
}