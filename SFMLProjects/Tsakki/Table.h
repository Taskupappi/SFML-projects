#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <array>

#include "Square.h"
#include "ChessPiece.h"

//#include "Player.h"


class Table
{
public:
	Table();
	~Table();

	void Draw(sf::RenderWindow* window);

	void Initialize();
	void Uninitialize();

	//calculates movement for every piece in the beginning of the turn
	//done only once each turn!
	bool CalculatePieceMovement();

	//set active piece's accessible squares to the "ToBeHighlighted" -vector
	void SetSquaresForHighlighting();
	//handles actual highlighting
	void HighlightSquares();

	//for mouse position
	bool SelectActivePiece(const sf::Vector2f mousePosition);
	//when you want to update using an existing piece
	bool SelectActivePiece(ChessPiece* piece);
	
	ChessPiece* GetActivePiece(){ return activePiece; };

	void PrintMouseTablePosition();
	std::vector<int[1][1]> GetLegalPositions();
	std::array<int, 2> MousePositionToTablePosition(sf::Vector2f mousePosition);

	//presets player movement before the buttons are selected
	void CheckMovement(const bool playerOneTurn, const sf::Vector2f mousePosition);
	
	//
	bool MoveActivePiece(const bool playerOneTurn, Square* squareToMove);
	
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

	bool CheckForCheck(const bool _playerOneTurn, Square* _squareToMove);

	Table* CopyTable();
	//Input stuff
	void Deselect();

	void DebugStuff();
private:
	std::vector<Square*> highlightedSquares;
	std::vector<Square*> squaresToBeHighlighted;
	
	ChessPiece* activePiece;
	ChessPiece* lastActivePiece;
	Square* board[8][8];
	std::vector<ChessPiece*> pieces;
	//ChessPiece* pieces[2][16];

	std::vector<int[1][1]> allMoves;
	std::array<int, 2> mouseToTablePosition;

	Square* squareToMove;
	int enPassantPosition[2];

	//Checkmate
	std::vector<ChessPiece*> PiecesInCheck;


	bool check[2]; //check[0] == player 1 && check[1] == player 2
};

#endif
