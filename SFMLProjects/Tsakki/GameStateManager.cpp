#include "GameStateManager.h"
#include "MainMenu.h"

GameStateManager::GameStateManager()
{
	states.push_back((GameState*)(new MainMenu((this))));
}

GameStateManager::~GameStateManager()
{
	std::list<GameState*>::iterator state; // = states.begin();

	while (states.empty())
	{
		state = states.begin();
		(*state)->Uninitialize();
		delete (*state);
	}
}

void GameStateManager::AddState(GameState* _state)
{
	states.push_back(_state);
	states.back()->Initialize();
}

void GameStateManager::PopState()
{
	states.pop_front();
}

void GameStateManager::Uninitialize()
{
	states.front()->Uninitialize();
}

void GameStateManager::Initialize()
{
	states.front()->Initialize();
}