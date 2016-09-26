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
	void HandleInput(sf::Vector2f mousePosition);

	void ShowAccessibleSquares();
	void HighlightSquare(const int x, const int y);
	
	ChessPiece* GetActivePiece(){ return activePiece; };
private:

	ChessPiece* activePiece;
	Square* board[8][8];
	ChessPiece* pieces[2][16];

	std::list<int[1][1]> allMoves;
};

#endif