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

	sf::Vector2u* screenResolution;
	Square* table [8][8];
	ChessPiece* pieces[2][16];
	std::list<GameState> state;

	bool playerOneTurn = true;
	sf::RenderWindow *window;
};

#endif
