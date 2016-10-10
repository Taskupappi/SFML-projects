#ifndef GAME_H
#define GAME_H

#include "GameStateManager.h"

class Game
{
public:
	Game();
	~Game();

	void Initialize();
	void Loop();
	void Uninitialize();
	void HandleInput();

private:
	sf::Vector2f mousePosition;
	std::array<int, 2> mouseBoardPosition;
	sf::Vector2u* screenResolution;
	sf::RenderWindow* window;
	GameStateManager stateManager;
};

#endif
