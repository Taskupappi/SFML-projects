#ifndef INGAME_H
#define INGAME_H

#include "GameState.h"
#include "Table.h"
#include "ChessPiece.h"

class InGame : public GameState
{
public:
	InGame(){};
	~InGame(){};

	//InGame state core
	void Initialize();
	void Loop(sf::RenderWindow* window);
	void Uninitialize();
	void Draw(sf::RenderWindow* _window);
	void HandleInput();

	//
	void HandleTurn();
	void EndTurn();

	//bool HandleInput();
	bool Move(int player);
private:

	Table board;
	bool playerOneTurn = true;


};
#endif

