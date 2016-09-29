#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"

#include "GameStateManager.h"

class Game
{
public:
	Game();
	~Game();

	void Initialize();
	void Loop(sf::RenderWindow* window);
	void Uninitialize();

private:
	sf::Vector2f mousePosition;
	sf::Vector2u* screenResolution;
	sf::RenderWindow* window;
	GameStateManager stateManager;
};

#endif
