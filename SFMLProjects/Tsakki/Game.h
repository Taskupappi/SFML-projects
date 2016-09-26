#ifndef GAME_H
#define GAME_H

#include "ChessPiece.h"
#include "Table.h"
#include <vector>
#include <list>

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
	void HandleInput();

private:
	sf::Vector2u* screenResolution;	
	std::list<GameState> state;
	bool playerOneTurn = true;
	sf::RenderWindow* window;
	Table table;

	//input
	sf::Vector2f mousePosition;
};

#endif
