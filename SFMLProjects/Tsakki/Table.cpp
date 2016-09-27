#include "Table.h"

Table::Table()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			//check the end of the last row

			//if y - 1 is not below zero are not in the first row
			if (y - 1 > -1)
			{
				bool lastIsWhite = board[7][y - 1]->isWhite;
				if (lastIsWhite)
				{
					//white squares
					if (x % 2 == 0)
						board[x][y] = new Square(true);
					//black squares
					else
						board[x][y] = new Square(false);
				}
				else
				{
					//white squares
					if (x % 2 == 0)
						board[x][y] = new Square(false);
					//black squares
					else
						board[x][y] = new Square(true);
				}
			}
			//first row
			else
			{
				//white squares
				if (x % 2 == 0)
					board[x][y] = new Square(true);
				//black squares
				else
					board[x][y] = new Square(false);
			}
		}
	}
	
	//player 1 pieces
	for (int i = 0; i < 8; i++)
	{
		//rooks
		if (i == 0 || i == 7)
		{
			pieces[0][i] = new ChessPiece(ChessPieceType::rook, 1, sf::Vector2i(i, 7));
		}
		//knights
		else if (i == 1 || i == 6)
		{
			pieces[0][i] = new ChessPiece(ChessPieceType::knight, 1, sf::Vector2i(i, 7));
		}
		//bishops
		else if (i == 2 || i == 5)
		{
			pieces[0][i] = new ChessPiece(ChessPieceType::bishop, 1, sf::Vector2i(i, 7));
		}
		//Queen
		else if (i == 3)
		{
			pieces[0][i] = new ChessPiece(ChessPieceType::queen, 1, sf::Vector2i(i, 7));
		}
		//King
		else if (i == 4)
		{
			pieces[0][i] = new ChessPiece(ChessPieceType::king, 1, sf::Vector2i(i, 7));
		}
	}

	for (int x = 0; x < 8; x++)
	{
		//pawns
		pieces[0][8 + x] = new ChessPiece(ChessPieceType::pawn, 1, sf::Vector2i(x, 6));
	}
	
	//player 2 pieces
	for (int i = 0; i < 8; i++)
	{
		//rooks
		if (i == 0 || i == 7)
		{
			pieces[1][i] = new ChessPiece(ChessPieceType::rook, 2, sf::Vector2i(i, 0));
		}
		//knights
		else if (i == 1 || i == 6)
		{
			pieces[1][i] = new ChessPiece(ChessPieceType::knight, 2, sf::Vector2i(i, 0));
		}
		//bishops
		else if (i == 2 || i == 5)
		{
			pieces[1][i] = new ChessPiece(ChessPieceType::bishop, 2, sf::Vector2i(i, 0));
		}
		//Queen
		else if (i == 3)
		{
			pieces[1][i] = new ChessPiece(ChessPieceType::queen, 2, sf::Vector2i(i, 0));
		}
		//King
		else if (i == 4)
		{
			pieces[1][i] = new ChessPiece(ChessPieceType::king, 2, sf::Vector2i(i, 0));
		}
	}

	for (int x = 0; x < 8; x++)
	{
		//pawns
		pieces[1][8 + x] = new ChessPiece(ChessPieceType::pawn, 2, sf::Vector2i(x, 1));
	}

	activePiece = nullptr;
}

Table::~Table()
{
	for (int i = 1; i > -1; i--)
	{
		for (int y = 15; y > -1; y--)
		{
			delete pieces[i][y];
		}
	}

	for (int i = 7; i > -1; i--)
	{
		for (int y = 7; y > -1; y--)
		{
			delete board[i][y];
		}
	}
}

void Table::Initialize()
{
	//place all table pieces
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[x][y]->sprite.setPosition((board[x][y]->sprite.getGlobalBounds().width * x) + 100.0f, (board[x][y]->sprite.getGlobalBounds().height * y) + 100.0f);
		}
	}

	//place all pieces on the table
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			pieces[x][y]->GetSprite().setPosition((board[pieces[x][y]->tablePosition.x][pieces[x][y]->tablePosition.y]->sprite.getPosition().x), (board[pieces[x][y]->tablePosition.x][pieces[x][y]->tablePosition.y]->sprite.getPosition().y));
		}
	}
}

void Table::Uninitialize()
{

	activePiece = nullptr;

	//for each (ChessPiece* piece in pieces)
	//{
	//	delete piece;
	//}

	/*for each (Square* square in board)
	{
		delete board;
	}*/

	////delete all table pieces
	//for (int x = 1; x > -1; x--)
	//{
	//	for (int y = 7; y > -1; y--)
	//	{
	//		delete pieces[x][y];
	//	}
	//}

	//for (int y = 0; y < 8; y++)
	//{
	//	for (int x = 0; x < 8; x++)
	//	{
	//		delete board[x][y];
	//	}
	//}
}

void Table::Draw(sf::RenderWindow* window)
{
	//draw all chess table squares
	for each (Square* square in board)
	{
		window->draw(square->sprite);
	}

	//highlight all the squares the chess piece could move to
	/*for each()
	{

	}*/

	for each (ChessPiece* piece in pieces)
	{
		if (piece != activePiece)
		{
			piece->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		}
	}

	//draw all the pieces on the chess table
	for each (ChessPiece* piece in pieces)
	{
		window->draw(piece->GetSprite());
	}

	if (activePiece)
	{
		activePiece->GetSprite().setColor(sf::Color(128, 128, 128, 255));
	}
}

void Table::HandleInput(sf::Vector2f mousePosition)
{

	//if mouse pressed, check if any of the chess pieces were selected
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				if (pieces[x][y]->GetSprite().getGlobalBounds().contains(mousePosition))
				{
					if (pieces[x][y]->player == 1)
					{
						activePiece = pieces[x][y];
					}
				}
			}
		}
	}

	if (activePiece && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		activePiece = nullptr;
	}
}

void Table::ShowAccessibleSquares()
{
	if (activePiece)
	{
		switch (activePiece->type)
		{
			case ChessPieceType::pawn:
			{
				if (activePiece->player == 1)
				{
					//check if there is a piece in front of the pawn
					//if yes, don't allow movement
					bool allowMovementForward = true;
					
					if (activePiece->tablePosition.y - 1 < 0)
					{
						for (int i = 0; i < 16; i++)
						{
							if ((pieces[0][i]->tablePosition.x == activePiece->tablePosition.x) && (pieces[0][i]->tablePosition.y == activePiece->tablePosition.y - 1))
							{
								allowMovementForward = false;
							}
							if ((pieces[1][i]->tablePosition.x == activePiece->tablePosition.x) && (pieces[1][i]->tablePosition.y == activePiece->tablePosition.y - 1))
							{
								allowMovementForward = false;
							}
						}
					}

					if (allowMovementForward)
					{
						//board[activePiece->tablePosition.x][activePiece->tablePosition.y - 1]->sprite.setColor(sf::Color(0, 255, 0, 255)
						coloredSquares.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y - 1]);						
					}

					
				}
				else if (activePiece->player == 2)
				{
					//check if there is a piece in front of the pawn
					//if yes, don't allow movement
					bool allowMovementForward = true;

					for (int i = 0; i < 16; i++)
					{
						if ((pieces[0][i]->tablePosition.x == activePiece->tablePosition.x) && (pieces[0][i]->tablePosition.y == activePiece->tablePosition.y + 1))
						{
							allowMovementForward = false;
						}
						if ((pieces[1][i]->tablePosition.x == activePiece->tablePosition.x) && (pieces[1][i]->tablePosition.y == activePiece->tablePosition.y + 1))
						{
							allowMovementForward = false;
						}
					}

					if (activePiece->tablePosition.y + 1 < 8 && allowMovementForward)
					{
						//highlight the available square

					}
				}

				break;
			}
			case ChessPieceType::knight:
			{
				if (activePiece->player == 1)
				{

				}
				break;
			}
			case ChessPieceType::rook:
			{
				if (activePiece->player == 1)
				{

				}
				break;
			}
			case ChessPieceType::bishop:
			{
				if (activePiece->player == 1)
				{

				}
				break;
			}
			case ChessPieceType::queen:
			{
				if (activePiece->player == 1)
				{

				}
				break;
			}
			case ChessPieceType::king:
			{
				if (activePiece->player == 1)
				{

				}
				break;
			}
			default:
				break;
		}
	}
}


void Table::HighlightSquare(const int x, const int y)
{

}