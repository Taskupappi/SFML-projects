#ifndef GAME_H
#define GAME_H

#include "ChessPiece.h"
#include "Square.h"
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


private:
	std::vector<ChessPiece> pieces;
	std::vector<Square> table;
	std::list<GameState> state;

	bool playerOneTurn = true;
	sf::RenderWindow *window;
};

#endif
