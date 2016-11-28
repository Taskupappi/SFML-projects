#ifndef INGAME_H
#define INGAME_H

#include "GameStateManager.h"
#include "GameState.h"
#include "Table.h"
#include "ChessPiece.h"
#include "TextManager.h"
#include "Network.h"


enum GAMETYPE
{
	HOST,
	JOIN,
	HOTSEAT,
	AI

};

class InGame : public GameState
{
public:
	InGame(GameStateManager* _stateManager, GAMETYPE type);
	~InGame(){};

	//InGame state core
	void Initialize();
	void Loop(sf::RenderWindow* window, const sf::Vector2f mousePosition,TextManager* textManager);
	void Uninitialize();
	void Draw(sf::RenderWindow* window, TextManager* textManager);
	void HandleInput(const sf::Event inputEvent, const sf::Vector2f mousePosition);

	//bool Move(const int player, const sf::Vector2f mousePosition);

	//
	void BeginTurn(sf::RenderWindow* window);
	bool HandleTurn(sf::RenderWindow* window, const sf::Vector2f mousePosition);
	void EndTurn();

	//bool HandleInput();
	bool Move();

	//text stuff
	void SetPlayerTurnText(TextManager* textManager);

	//networking
	void SetupHost(const bool isHost);

private:
	bool beginTurnStep = true;
	bool endTurn = false;
	Table board;
	bool playerOneTurn = true;
	std::array<int, 2> mouseToBoardPosition;
	//bool checkmate[2] {false, false};
	GAMETYPE type;

	//network
	bool isHost = false;
	Network *network;
};
#endif

