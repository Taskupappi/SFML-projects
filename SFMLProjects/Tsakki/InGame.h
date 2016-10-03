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
	void Loop(sf::RenderWindow* window, const sf::Vector2f mousePosition);
	void Uninitialize();
	void Draw(sf::RenderWindow* window);
	void HandleInput(const sf::Event event, const sf::Vector2f mousePosition);

	//bool Move(const int player, const sf::Vector2f mousePosition);

	//
	bool HandleTurn(sf::RenderWindow* window, const sf::Vector2f mousePosition);
	void EndTurn();

	//bool HandleInput();
	//bool Move(int player, sf::RenderWindow* _window, const sf::Vector2f mousePosition);

private:

	Table board;
	bool playerOneTurn = true;
};
#endif

