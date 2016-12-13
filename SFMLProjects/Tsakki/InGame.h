#ifndef INGAME_H
#define INGAME_H

#include "MoveConventer.h"
#include "Network.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Table.h"
#include "ChessPiece.h"
#include "TextManager.h"
#include "Player.h"


enum class GAMETYPE
{
	HOST,
	JOIN,
	HOTSEAT,
	AGAINSTAI
};

class InGame : public GameState
{
public:
	InGame(GameStateManager* _stateManager, GAMETYPE gameType);
	~InGame(){};

	//InGame state core
	void Initialize();
	void Loop(sf::RenderWindow* window, const sf::Vector2f mousePosition,TextManager* textManager);
	void Uninitialize();
	void Draw(sf::RenderWindow* window, TextManager* textManager);
	void HandleInput(const sf::Event inputEvent, const sf::Vector2f mousePosition);

	void DecideColor();

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

	bool WaitForMoveFromOpponent();

	std::string ConvertToString(std::pair<sf::Vector2i, sf::Vector2i> pair);
	std::pair<sf::Vector2i, sf::Vector2i> ConvertToVec(std::string move);
	std::pair<sf::Vector2i, sf::Vector2i> ConvertIntIntoPair(int _toBeConverter);


private:
	bool beginTurnStep = true;
	bool endTurn = false;
	Table board;
	bool whitePlayerTurn = true;
	std::array<int, 2> mouseToBoardPosition;
	//bool checkmate[2] {false, false};
	GAMETYPE gameType;

	//network
	bool isHost = false;
	Network *network;
	Player players[2]; //player 0 is this player, player 1 is the opponent. 1 == white, 2 == black
	std::string lastMove;
	std::string currentMove;
};
#endif

