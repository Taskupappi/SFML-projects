#include "Table.h"

#include <iostream>

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
						board[x][y] = new Square(true, x, y);
					//black squares
					else
						board[x][y] = new Square(false, x, y);
				}
				else
				{
					//white squares
					if (x % 2 == 0)
						board[x][y] = new Square(false, x, y);
					//black squares
					else
						board[x][y] = new Square(true, x, y);
				}
			}
			//first row
			else
			{
				//white squares
				if (x % 2 == 0)
					board[x][y] = new Square(true, x, y);
				//black squares
				else
					board[x][y] = new Square(false, x, y);
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
	lastActivePiece = nullptr;

	delete activePiece;
	delete lastActivePiece;

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
		square->sprite.setColor(sf::Color(255, 0, 0, 255));
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
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			if (pieces[x][y]->GetSprite().getGlobalBounds().contains(mousePosition))
			{
				if (activePiece)
				{
					lastActivePiece = activePiece;
				}
				else
				{
					lastActivePiece = nullptr;
				}
				
				activePiece = pieces[x][y];

				if (lastActivePiece == nullptr)
				{
					return false;
				}					
				else
				{
					return true;
				}										
			}
		}
	}
	return false;
}

bool Table::SelectActivePiece(ChessPiece* _piece)
{
	lastActivePiece = activePiece;
	activePiece = _piece;
	return true;
}

void Table::ShowAccessibleSquares()
{
	if (activePiece)
	{
		squaresToBeHighlighted.clear();

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
						squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y - 1]);

						if (!activePiece->hasMoved)
						{
							bool allowTwoSquareMovent = true;

							for (int i = 0; i < 16; i++)
							{
								if ((pieces[0][i]->tablePosition.x == activePiece->tablePosition.x) && (pieces[0][i]->tablePosition.y == activePiece->tablePosition.y - 2))
								{
									allowTwoSquareMovent = false;
								}
								if ((pieces[1][i]->tablePosition.x == activePiece->tablePosition.x) && (pieces[1][i]->tablePosition.y == activePiece->tablePosition.y - 2))
								{
									allowTwoSquareMovent = false;
								}
							}

							if (allowTwoSquareMovent)
							{
								squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y - 2]);
							}
						}
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

						if (!activePiece->hasMoved)
						{
							bool allowTwoSquareMovent = true;

							for (int i = 0; i < 16; i++)
							{
								if ((pieces[0][i]->tablePosition.x == activePiece->tablePosition.x) && (pieces[0][i]->tablePosition.y == activePiece->tablePosition.y + 2))
								{
									allowTwoSquareMovent = false;
								}
								if ((pieces[1][i]->tablePosition.x == activePiece->tablePosition.x) && (pieces[1][i]->tablePosition.y == activePiece->tablePosition.y + 2))
								{
									allowTwoSquareMovent = false;
								}
							}

							if (allowTwoSquareMovent)
							{
								squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y + 2]);
							}
						}
					}
				}

				break;
			}
			case ChessPieceType::knight:
			{
				if (activePiece->tablePosition.x - 1 > -1 && activePiece->tablePosition.y - 2 > -1)
				{
					squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y - 2]);
				}
				if (activePiece->tablePosition.x + 1 < 8 && activePiece->tablePosition.y - 2 > -1)
				{
					squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y - 2]);
				}
				if (activePiece->tablePosition.x - 1 > -1 && activePiece->tablePosition.y + 2 < 8)
				{
					squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y + 2]);
				}
				if (activePiece->tablePosition.x + 1 < 8 && activePiece->tablePosition.y + 2 < 8)
				{
					squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y + 2]);
				}
				if (activePiece->tablePosition.x + 2 < 8 && activePiece->tablePosition.y - 1 > -1)
				{
					squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 2][activePiece->tablePosition.y - 1]);
				}
				if (activePiece->tablePosition.x + 2 < 8 && activePiece->tablePosition.y + 1 < 8)
				{
					squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 2][activePiece->tablePosition.y + 1]);
				}
				if (activePiece->tablePosition.x - 2 > -1 && activePiece->tablePosition.y - 1 > -1)
				{
					squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 2][activePiece->tablePosition.y - 1]);
				}
				break;
			}
			case ChessPieceType::rook:
			{
				ChessPiece* tempPiece = nullptr;
				int indexTeam = 0;
				int indexPiece = 0;

				//infront S-N
				for (; indexTeam < 2; indexTeam++)
				{
					for (; indexPiece < 16; indexPiece++)
					{
						//find the closest piece in front of the rook
						if (pieces[indexTeam][indexPiece]->tablePosition.x == activePiece->tablePosition.x && pieces[indexTeam][indexPiece]->tablePosition.y < activePiece->tablePosition.y)
						{
							//set the first closest position
							if (tempPiece == nullptr)
							{
								tempPiece = pieces[indexTeam][indexPiece];
							}

							//if someone is closer to the rook and infront of it, set its position as the closest position
							if (tempPiece->tablePosition.y < pieces[indexTeam][indexPiece]->tablePosition.y && pieces[indexTeam][indexPiece]->tablePosition.y < activePiece->tablePosition.y)
							{
								tempPiece = pieces[indexTeam][indexPiece];
							}
						}
					}
				}
				if (tempPiece == nullptr)
				{
					//we can highlight every square in front of the rook
					for (int i = activePiece->tablePosition.y - 1; i > 0; i--)
					{
						squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][i]);
					}
				}
				else
				{
					//since there is someone in front of the rook, we can only move the distance in between....
					for (int i = (activePiece->tablePosition.y - tempPiece->tablePosition.y) - 1; i > 0; i--)
					{
						squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y - i]);
					}

					//..unless the piece is enemy. Then we can eat that as well
					if (tempPiece->player != activePiece->player)
					{
						squaresToBeHighlighted.push_back(board[tempPiece->tablePosition.x][tempPiece->tablePosition.y]);
					}

				}
					
				//behind N-S
				tempPiece = nullptr;
				indexTeam = 0;
				indexPiece = 0;

				for (; indexTeam < 2; indexTeam++)
				{
					for (; indexPiece < 16; indexPiece++)
					{
						//find the closest piece behind the rook
						if (pieces[indexTeam][indexPiece]->tablePosition.x == activePiece->tablePosition.x && pieces[indexTeam][indexPiece]->tablePosition.y > activePiece->tablePosition.y)
						{
							//set the first closest position
							if (tempPiece == nullptr)
							{
								tempPiece = pieces[indexTeam][indexPiece];
							}

							//if someone is closer to the rook and infront of it, set its position as the closest position
							if (tempPiece->tablePosition.y > pieces[indexTeam][indexPiece]->tablePosition.y && pieces[indexTeam][indexPiece]->tablePosition.y > activePiece->tablePosition.y)
							{
								tempPiece = pieces[indexTeam][indexPiece];
							}
						}
					}
				}
				if (tempPiece == nullptr)
				{
					//we can highlight every square behind of the rook
					for (int i = activePiece->tablePosition.y + 1; i < 8; i++)
					{
						squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][i]);						
					}
				}
				else
				{
					//since there is someone behind of the rook, we can only move the distance in between....
					for (int i = (tempPiece->tablePosition.y - activePiece->tablePosition.y) - 1; i > 0; i--)
					{
						squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y + i]);
					}

					//..unless the piece is enemy. Then we can eat that as well
					if (tempPiece->player != activePiece->player)
					{
						squaresToBeHighlighted.push_back(board[tempPiece->tablePosition.x][tempPiece->tablePosition.y]);
					}

				}

				//left side
				tempPiece = nullptr;
				indexTeam = 0;
				indexPiece = 0;

				for (; indexTeam < 2; indexTeam++)
				{
					for (; indexPiece < 16; indexPiece++)
					{
						//find the closest piece on the left side of the rook
						if (pieces[indexTeam][indexPiece]->tablePosition.x < activePiece->tablePosition.x && pieces[indexTeam][indexPiece]->tablePosition.y == activePiece->tablePosition.y)
						{
							//set the first closest position
							if (tempPiece == nullptr)
							{
								tempPiece = pieces[indexTeam][indexPiece];
							}

							//if someone is closer to the rook on the left side of it, set its position as the closest position
							if (tempPiece->tablePosition.x < pieces[indexTeam][indexPiece]->tablePosition.x && pieces[indexTeam][indexPiece]->tablePosition.x < activePiece->tablePosition.x)
							{
								tempPiece = pieces[indexTeam][indexPiece];
							}
						}
					}
				}
				if (tempPiece == nullptr)
				{
					//we can highlight every square on the left side of the rook
					for (int i = 0; i < activePiece->tablePosition.x; i++)
					{
						squaresToBeHighlighted.push_back(board[i][activePiece->tablePosition.y]);
					}
				}
				else
				{
					//since there is someone on the left side of the rook, we can only move the distance in between....
					for (int i = (activePiece->tablePosition.x - tempPiece->tablePosition.x) - 1; i > tempPiece->tablePosition.x; i--)
					{
						squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - i][activePiece->tablePosition.y]);
					}

					//..unless the piece is enemy. Then we can eat that as well
					if (tempPiece->player != activePiece->player)
					{
						squaresToBeHighlighted.push_back(board[tempPiece->tablePosition.x][tempPiece->tablePosition.y]);
					}

				}

				//right side
				tempPiece = nullptr;
				indexTeam = 0;
				indexPiece = 0;

				for (; indexTeam < 2; indexTeam++)
				{
					for (; indexPiece < 16; indexPiece++)
					{
						//find the closest piece on the left side of the rook
						if (pieces[indexTeam][indexPiece]->tablePosition.x > activePiece->tablePosition.x && pieces[indexTeam][indexPiece]->tablePosition.y == activePiece->tablePosition.y)
						{
							//set the first closest position
							if (tempPiece == nullptr)
							{
								tempPiece = pieces[indexTeam][indexPiece];
							}

							//if someone is closer to the rook on the left side of it, set its position as the closest position
							if (tempPiece->tablePosition.x > pieces[indexTeam][indexPiece]->tablePosition.x && pieces[indexTeam][indexPiece]->tablePosition.x > activePiece->tablePosition.x)
							{
								tempPiece = pieces[indexTeam][indexPiece];
							}
						}
					}
				}
				if (tempPiece == nullptr)
				{
					//we can highlight every square on the right side of the rook
					for (int i = 7; i > activePiece->tablePosition.x; i--)
					{
						squaresToBeHighlighted.push_back(board[i][activePiece->tablePosition.y]);
					}
				}
				else
				{
					//since there is someone on the left side of the rook, we can only move the distance in between....
					for (int i = (tempPiece->tablePosition.x - activePiece->tablePosition.x) - 1; i > activePiece->tablePosition.x; i--)
					{
						squaresToBeHighlighted.push_back(board[tempPiece->tablePosition.x - i][tempPiece->tablePosition.y]);
					}

					//..unless the piece is enemy. Then we can eat that as well
					if (tempPiece->player != activePiece->player)
					{
						squaresToBeHighlighted.push_back(board[tempPiece->tablePosition.x][tempPiece->tablePosition.y]);
					}

				}


				tempPiece = nullptr;
				delete tempPiece;
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
	if (activePiece != lastActivePiece)
	{	
		//reset all the highlighted squares
		std::vector<Square*>::iterator highlightedSquaresIt = highlightedSquares.begin();

		while (highlightedSquaresIt != this->highlightedSquares.end())
		{			
			(*highlightedSquaresIt)->sprite.setColor(sf::Color(255, 255, 255, 255));
			highlightedSquaresIt++;
		}

		highlightedSquares.clear();

		//add squares that are supposed to be highlighted and highlight them
		std::vector<Square*>::iterator squaresToHightlightIt = squaresToBeHighlighted.begin();

		while (squaresToHightlightIt != this->squaresToBeHighlighted.end())
		{
			highlightedSquares.push_back((*squaresToHightlightIt));
			squaresToHightlightIt++;
		}

		for each (Square* square in highlightedSquares)
		{
			square->sprite.setColor(sf::Color(255, 0, 255, 255));
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

void Table::ClearActivePiece()
{
	if (lastActivePiece)
	{
		lastActivePiece->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	if (activePiece)
	{
		lastActivePiece = activePiece;
	}

	if (activePiece)
	{
		activePiece->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}
	
	squareToMove = nullptr;
	activePiece = nullptr;
}

std::array<int, 2> Table::MousePositionToTablePosition(sf::Vector2f mousePosition)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (board[x][y]->sprite.getGlobalBounds().contains(mousePosition))
			{
				mouseToTablePosition[0] = x;
				mouseToTablePosition[1] = y;
				return mouseToTablePosition;
			}
		}
	}
	return mouseToTablePosition;
}

void Table::PrintMouseTablePosition()
{
	std::cout << "\n" << "mouse position on the table:\n" << "x: " << mouseToTablePosition[0] << "\ny: " << mouseToTablePosition[1] << std::endl;
}

void Table::CheckMovement(const bool _playerOneTurn, const sf::Vector2f _mousePosition)
{
	if (activePiece)
	{
		if ((activePiece->player == 1 && _playerOneTurn) || (activePiece->player == 2 && !_playerOneTurn))
		{
			for each (Square* square in highlightedSquares)
			{
				if (square->tablePosition.x == mouseToTablePosition[0] && square->tablePosition.y == mouseToTablePosition[1])
				{
					//set square where the piece will move when the turn is handled
					squareToMove = square;
					return;
				}
			}
		}		
	}
	
	//ChessPiece* piece = GetPieceAtPosition(MousePositionToTablePosition(_mousePosition));

	if (GetPieceAtPosition(MousePositionToTablePosition(_mousePosition)))
	{
		SelectActivePiece(GetPieceAtPosition(MousePositionToTablePosition(_mousePosition)));
	}
	else
	{
		//there was no chess piece in the pressed square, nor was it a legal move. Thus we clear active piece
		ClearActivePiece();
	}
}

bool Table::MoveActivePiece(const bool _playerOneTurn, Square* _squareToMove)
{
	if (activePiece)
	{
		activePiece->tablePosition = _squareToMove->tablePosition;
		activePiece->GetSprite().setPosition(_squareToMove->sprite.getPosition().x, _squareToMove->sprite.getPosition().y);
		ClearActivePiece();
		return true;
	}
	else
	{
		return false;
	}
}

ChessPiece* Table::GetPieceAtPosition(const std::array<int, 2> _position)
{
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			if (pieces[i][j]->tablePosition.x == _position[0] && pieces[i][j]->tablePosition.y == _position[1])
			{
				return pieces[i][j];
			}
		}
	}

	return nullptr;
}


