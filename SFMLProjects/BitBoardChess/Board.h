#ifndef BOARD_H
#define BOARD_H

#define BOARD_SQUARE_NUMBER 120
#define MAXGAMEMOVES 4096

typedef uint64_t Bitboard;

//GLOBALS
extern int sq120ToSq64[BOARD_SQUARE_NUMBER]
extern int sq64ToSq120[64]

extern void InitSq120To64();

//MACRO
#define FILERANKTOSQUARE(file, rank) ((21 + (file)) + (rank) * 10)

typedef struct BOARDHISTORY
{
	int move;
	int castlePermission;
	int enPasse;
	int fiftyMoveRule;
	Bitboard positionKey;
};

enum
{
	EMPTY, P, N, B, R, Q, K, p, n, b, r, q, k
};

enum
{
	FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE
};

enum
{
RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_9, RANK_NONE
};

enum
{
	WHITE, BLACK, BOTH
};

enum
{
	WHITEKINGCASTLING = 1, WHITEQUEENCASTLING = 2, BLACKKINGCASTLING = 4, BLACKQUEENCASTLING = 8
};

enum
{
	A1 = 0, B1, C1, D1, E1, F1, G1, H1,
	A2 = 8, B2, C1, D2, E2, F2, G2, H2,
	A3 = 16, B3,C1, D3, E3, F3, G3, H3,
	A4 = 24, B4,C1, D4, E4, F4, G4, H4,
	A5 = 32, B5,C1, D5, E5, F5, G5, H5,
	A6 = 40, B6,C1, D6, E6, F6, G6, H6,
	A7 = 48, B7,C1, D7, E7, F7, G7, H7,
	A8 = 56, B8,C1, D8, E8, F8, G8, H8, NO_SQ
};

enum
{
	FALSE, TRUE
};

class Board
{
public:
	Board();
	~Board();

	void Init();

private:

	int pieces[120];
	
	Bitboard pawns[3]; //one for white, one black, one for both

	int KingSq[];

	int side;
	int enPasse;
	int fiftyMoveRule;
	int ply;
	int historyply;

	Bitboard positionKey;

	int castlePermission;

	int pieceNumber[13];

	int bigPieces[3]; //one for white, one black, one for both
	int majorPieces[3]; //one for white, one black, one for both
	int minorPieces[3]; //one for white, one black, one for both

	BOARDHISTORY history[MAXGAMEMOVES];
}

#endif