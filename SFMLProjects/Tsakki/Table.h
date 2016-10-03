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

	void Initialize();
	void Uninitialize();

	void ShowAccessibleSquares();
	void HighlightSquares();

	bool SelectActivePiece(const sf::Vector2f mousePosition);
	ChessPiece* GetActivePiece(){ return activePiece; };

	void PrintMouseTablePosition();
	std::vector<int[1][1]> GetLegalPositions();
	std::array<int, 2> MousePositionToTablePosition(sf::Vector2f mousePosition);

	//
	bool Move();

	//stuff for ending the turn
	void ClearHighlights();
	void ClearActivePiece();
	
	std::vector<Square*> GetHighlightedSquares(){ return highlightedSquares; };
private:
	std::vector<Square*> highlightedSquares;
	std::vector<Square*> squaresToBeHighlighted;
	
	ChessPiece* activePiece;
	ChessPiece* lastActivePiece;
	Square* board[8][8];
	ChessPiece* pieces[2][16];

	std::vector<int[1][1]> allMoves;
	std::array<int, 2> mouseToTablePosition;
};

#endif