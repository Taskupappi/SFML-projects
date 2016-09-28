#ifndef TABLE_H
#define TABLE_H

#include <list>

#include "Square.h"
#include "ChessPiece.h"

class Table
{
public:
	Table();
	~Table();

	void Draw(sf::RenderWindow* window);

	void Initialize();
	void Uninitialize();

	bool HandleInput(sf::Vector2f mousePosition);

	void ShowAccessibleSquares();
	void HighlightSquare(const int x, const int y);
	void HighlightSquares();

	ChessPiece* GetActivePiece(){ return activePiece; };

	//
	bool Move();

	//stuff for ending the turn
	void ClearHighlights();


private:
	std::list<Square*> highlightedSquares;
	std::list<Square*> squaresToBeHighlighted;
	
	ChessPiece* activePiece;
	ChessPiece* lastActivePiece;
	Square* board[8][8];
	ChessPiece* pieces[2][16];

	std::list<int[1][1]> allMoves;
};

#endif