#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <array>

#include "Square.h"
#include "ChessPiece.h"


class Table
{
public:
	Table();
	~Table();

	void Draw(sf::RenderWindow* window);


	void Initialize(Player players[2]);
	void Uninitialize();

	//used to update where pieces can move whenever the state of the talbe would change
	bool CalculatePieceMovement(ChessPiece* piece);
	void CalculatePieceMovementForEachPiece();

	//set active piece's accessible squares to the "ToBeHighlighted" -vector
	void SetSquaresForHighlighting();
	//handles actual highlighting
	void HighlightSquares();

	//for mouse position
	bool SelectActivePiece(const sf::Vector2f mousePosition);
	//when you want to update using an existing piece
	bool SelectActivePiece(ChessPiece* piece);
	//for network
	bool SelectActivePiece(sf::Vector2i piecePosition);
	
	ChessPiece* GetActivePiece(){ return activePiece; };

	void PrintMouseTablePosition();
	std::vector<int[1][1]> GetLegalPositions();
	std::array<int, 2> MousePositionToTablePosition(sf::Vector2f mousePosition);

	//presets player movement before the buttons are selected
	void CheckMovement(const bool whitePlayerTurn, const sf::Vector2f mousePosition);
	
	//
	void UpdateCheckBoolStatus();

	bool MoveOpponent(const bool whitePlayerTurn, std::pair<sf::Vector2i, sf::Vector2i> modeData);

	//
	bool MoveActivePiece(const bool whitePlayerTurn, Square* squareToMove);
	
	void EatPiece(ChessPiece* pieceToDelete);

	ChessPiece* GetPieceAtPosition(const std::array<int, 2> position);

	//used to move chess piece or set the position
	void SetOnTable(ChessPiece* piece, sf::Vector2i position);
	void SetOnTable(ChessPiece* piece, Square* squareToMove);
	Square* GetSquareAtPosition(sf::Vector2i position);

	//stuff for ending the turn
	void ClearHighlights();
	void ClearActivePiece();
	
	std::vector<Square*> GetHighlightedSquares(){ return highlightedSquares; };
	Square* GetSquareToMove(){ return squareToMove; };
	void SetSquareToMove();
	void ClearSquareToMove(){ squareToMove = nullptr; };
	void SetSquareToMove(sf::Vector2i position);

	bool CheckForCheck(const bool _playerOneTurn, Square* _squareToMove);

	bool Checkmate(const bool _playerOneTurn);

	Table* CopyTable();
	//Input stuff
	void Deselect();

	void DebugStuff();

	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> GetAllMoves() { return allMoves; };

	std::vector<ChessPiece*> GetPieces() { return pieces; };
private:
	std::vector<Square*> highlightedSquares;
	std::vector<Square*> squaresToBeHighlighted;
	
	ChessPiece* activePiece;
	ChessPiece* lastActivePiece;
	Square* board[8][8];
	std::vector<ChessPiece*> pieces;
	//ChessPiece* pieces[2][16];

	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> allMoves;
	std::array<int, 2> mouseToTablePosition;

	Square* squareToMove;
	int enPassantPosition[2];

	//Checkmate
	std::vector<ChessPiece*> PiecesInCheck;


	bool check[2]; //check[0] == player 1 && check[1] == player 2
	bool checkmate[2]; //checkmate[0] == player 1 && check[1] == player 2
};
#endif
