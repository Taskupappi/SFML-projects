#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SFML\Graphics.hpp"

class GameState
{
public:
	GameState(){};
	~GameState(){};

	//GameState core
	virtual void Initialize(){};
	virtual void Loop(sf::RenderWindow* window, const sf::Vector2f mousePosition){};
	virtual void Uninitialize(){};
	virtual void Draw(){};
	virtual void HandleInput(const sf::Event::EventType event){};
};

#endif
