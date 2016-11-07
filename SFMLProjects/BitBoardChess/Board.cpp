#include "Board.h"

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init()
{
	InintSq120To64();
}

void InintSq120To64()
{
	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int currentSquare = A1;
	int square64 = 0;

	for (int index = 0; index < BOARD_SQUARE_NUMBER; ++index)
	{
		sq120ToSq64[index] = 65; //this won't be on the board
	}

	for (index = 0; index < 64; ++index)
	{
		sq64ToSq120[index] = 120; //this won't be on the board
	}

	for (rank = RANK_1; rank <= RANK_8; ++rank)
	{
		for (file = FILE_A; file <= FILE_H; ++file)
		{
			currentSquare = FILERANKTOSQUARE(file, rank);
			sq64ToSq120[square64] = currentSquare;
			sq120ToSq64[currentSquare] = square64;
			square64++;
		}
	}
}