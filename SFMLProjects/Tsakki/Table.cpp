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
	lastActivePiece = nullptr;
	//highlightedSquares = new std::list<Square*>();
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
	for each (Square* square in highlightedSquares)
	{
		square->sprite.setColor(sf::Color(128, 128, 128, 255));
	}

	//draw all squares of the table
	for each (Square* square in board)
	{
		window->draw(square->sprite);
	}

	if (activePiece)
	{
		if (lastActivePiece != activePiece && lastActivePiece)
		{
			lastActivePiece->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		}

		activePiece->GetSprite().setColor(sf::Color(128, 128, 128, 255));
	}

	//draw all the pieces on the chess table
	for each (ChessPiece* piece in pieces)
	{
		window->draw(piece->GetSprite());
	}
}

bool Table::SelectActivePiece(const sf::Vector2f mousePosition)
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
						lastActivePiece = activePiece;
						activePiece = pieces[x][y];
						return true;					
				}
			}
		}
	}
	else if (activePiece && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		activePiece = nullptr;
	}

	return false;
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
					
					if (activePiece->tablePosition.y - 1 > -1)
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
						squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y - 1]);
						
						  

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
						squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y + 1]);
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

	HighlightSquares();
}

void Table::HighlightSquares()
{
	if (activePiece == lastActivePiece)
	{
		return;
	}
	else
	{
		//reset all the highlighted squares
		std::vector<Square*>::iterator highlightedSquaresIt = highlightedSquares.begin();

		while (highlightedSquaresIt != this->highlightedSquares.end())
		{			
			(*highlightedSquaresIt)->sprite.setColor(sf::Color(255, 255, 255, 255));
			highlightedSquaresIt++;
		}

		highlightedSquares.clear();

		//add the new highlighted squares and highlight them
		std::vector<Square*>::iterator squaresToHightlightIt = squaresToBeHighlighted.begin();

		while (squaresToHightlightIt != this->squaresToBeHighlighted.end())
		{
			(*squaresToHightlightIt)->sprite.setColor(sf::Color(255, 0, 255, 255));
			squaresToHightlightIt++;
		}

		for each (Square* square in squaresToBeHighlighted)
		{
			highlightedSquares.push_back(square);
		}

		//empty the squaresToBeHighlighted so it won't hold any unnecessary squares
		squaresToBeHighlighted.clear();	
	}
}

void Table::ClearHighlights()
{
	//make sure everything is back to normal
	for each (Square* square in highlightedSquares)
	{
		square->sprite.setColor(sf::Color(255, 255, 255, 255));
	}

	highlightedSquares.clear();

	//no need to highlight these, so they can be just cleared from the lsit
	squaresToBeHighlighted.clear();

}

std::array<int, 2> Table::MousePositionToTablePosition(sf::Vector2f mousePosition)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (board[x][y]->sprite.getGlobalBounds().contains(mousePosition))
			{
				mouseToTablePosition[1] = x;
				mouseToTablePosition[2] = y;
				printf("mouse to table x: %f y: %f ", mouseToTablePosition[1], mouseToTablePosition[1]);
				return mouseToTablePosition;
			}
		}
	}
}