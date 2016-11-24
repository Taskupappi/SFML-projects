#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SFML\Graphics.hpp"
#include "TextManager.h"
#include "GameStateManager.h"

class GameState
{
public:
	GameState(){};
	~GameState(){};

	GameStateManager* stateManager;

	//GameState core
	virtual void Initialize(){};
	virtual void Loop(sf::RenderWindow* window, const sf::Vector2f mousePosition, TextManager* textManager){};
	virtual void Uninitialize(){};
	virtual void Draw(){};
	virtual void HandleInput(const sf::Event inputEvent, const sf::Vector2f mousePosition){};
};

#endif
