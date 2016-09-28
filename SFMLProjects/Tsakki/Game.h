#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include <queue>

#include "GameStateManager.h"
#include "ChessPiece.h"
#include "Table.h"

class Game
{
public:
	Game();
	~Game();

	void Initialize();
	void Loop();
	void Uninitialize();
	void Draw();

	bool HandleInput();
	bool Move();

	void HandleTurn();
	void EndTurn();

private:
	sf::Vector2u* screenResolution;	

	GameStateManager stateManager;

	bool playerOneTurn = true;
	sf::RenderWindow* window;
	Table table;

	//players


	//input
	sf::Vector2f mousePosition;

	std::queue<int> turnOrder;
};

#endif
