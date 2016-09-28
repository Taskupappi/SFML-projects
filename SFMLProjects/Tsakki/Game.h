#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include <queue>

#include "ChessPiece.h"
#include "Table.h"


enum GameState
{
	PAUSE,
	MAINMENU,
	RUNNING
};

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
	std::list<GameState> state;
	bool playerOneTurn = true;
	sf::RenderWindow* window;
	Table table;

	//players


	//input
	sf::Vector2f mousePosition;

	std::queue<int> turnOrder;
};

#endif
