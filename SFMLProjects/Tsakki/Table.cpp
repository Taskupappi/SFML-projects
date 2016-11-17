#include "Table.h"

#include <iostream>

Table::Table()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			//check the end of the last row
			//white squares
			if ((x + y) % 2 == 0)
				board[x][y] = new Square(true, x, y);
			//black squares
			else
				board[x][y] = new Square(false, x, y);
		}
	}

	activePiece = nullptr;
	lastActivePiece = nullptr;
	enPassantPosition[0] = -12;
	enPassantPosition[1] = -12;

	check[0] = false;
	check[1] = false;
}

Table::~Table()
{
	std::vector<ChessPiece*>::iterator piece = pieces.begin();
	for (; piece != pieces.end(); piece++)
	{
		delete (*piece);
		piece = pieces.erase(piece);

		if (piece == pieces.end())
			break;
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
	//player 1 pieces
	for (int i = 0; i < 8; i++)
	{
		//rooks
		if (i == 0 || i == 7)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::rook, 1));
			pieces.back()->tablePosition = sf::Vector2i(i, 7);
		}
		//knights
		else if (i == 1 || i == 6)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::knight, 1));
			pieces.back()->tablePosition = sf::Vector2i(i, 7);
		}
		//bishops
		else if (i == 2 || i == 5)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::bishop, 1));
			pieces.back()->tablePosition = sf::Vector2i(i, 7);
		}
		//Queen
		else if (i == 3)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::queen, 1));
			pieces.back()->tablePosition = sf::Vector2i(i, 7);
		}
		//King
		else if (i == 4)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::king, 1));
			pieces.back()->tablePosition = sf::Vector2i(i, 7);
		}
	}

	for (int x = 0; x < 8; x++)
	{
		//pawns
		pieces.push_back(new ChessPiece(ChessPieceType::pawn, 1));
		pieces.back()->tablePosition = sf::Vector2i(x, 6);
	}

	//player 2 pieces
	for (int i = 0; i < 8; i++)
	{
		//rooks
		if (i == 0 || i == 7)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::rook, 2));
			pieces.back()->tablePosition = sf::Vector2i(i, 0);
		}
		//knights
		else if (i == 1 || i == 6)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::knight, 2));
			pieces.back()->tablePosition = sf::Vector2i(i, 0);
		}
		//bishops
		else if (i == 2 || i == 5)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::bishop, 2));
			pieces.back()->tablePosition = sf::Vector2i(i, 0);
		}
		//Queen
		else if (i == 3)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::queen, 2));
			pieces.back()->tablePosition = sf::Vector2i(i, 0);
		}
		//King
		else if (i == 4)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::king, 2));
			pieces.back()->tablePosition = sf::Vector2i(i, 0);
		}
	}

	for (int x = 0; x < 8; x++)
	{
		//pawns
		pieces.push_back(new ChessPiece(ChessPieceType::pawn, 2));
		pieces.back()->tablePosition = sf::Vector2i(x, 1);
	}

	//place all table pieces
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[x][y]->sprite.setPosition((board[x][y]->sprite.getGlobalBounds().width * x) + 100.0f, (board[x][y]->sprite.getGlobalBounds().height * y) + 100.0f);
		}
	}

	//place all pieces on the table
	for each (ChessPiece* piece in pieces)
	{
		SetOnTable(piece, piece->tablePosition);
	}
}

void Table::Uninitialize()
{
	activePiece = nullptr;
	lastActivePiece = nullptr;

	delete activePiece;
	delete lastActivePiece;
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
		if (piece != nullptr)
		{
			window->draw(piece->GetSprite());
		}
	}

	DebugStuff();
}

bool Table::SelectActivePiece(const sf::Vector2f mousePosition)
{
	//if mouse pressed, check if any of the chess pieces were selected
	for each (ChessPiece* piece in pieces)
	{
		if (piece->GetSprite().getGlobalBounds().contains(mousePosition))
		{
			if (activePiece)
			{				
				lastActivePiece = activePiece;
			}
			else
			{
				lastActivePiece = nullptr;
			}

			activePiece = piece;

			if (lastActivePiece == nullptr)
			{
				return false;
			}
			else
			{
				return true;
			}

			if (lastActivePiece == activePiece)
			{
				ClearHighlights();
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

void Table::SetSquaresForHighlighting()
{
	if (activePiece)
	{
		if (activePiece != lastActivePiece)
		{
			squaresToBeHighlighted.clear();

			for (std::vector<sf::Vector2i>::iterator squareCoordinates = activePiece->possibleMoves.begin(); squareCoordinates != activePiece->possibleMoves.end(); squareCoordinates++)
			{
				squaresToBeHighlighted.push_back(board[(*squareCoordinates).x][(*squareCoordinates).y]);
			}

			HighlightSquares();
		}
	}
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
		Deselect();
	}
}

Table* Table::CopyTable()
{
	Table* copyTable = new Table();

	for each (ChessPiece* piece in pieces)
	{
		copyTable->pieces.push_back(new ChessPiece(piece->type, piece->player));
		copyTable->pieces.back()->tablePosition = piece->tablePosition;
		copyTable->pieces.back()->lastPosition = piece->lastPosition;
		copyTable->pieces.back()->possibleMoves = piece->possibleMoves;
		copyTable->pieces.back()->checkingMoves = piece->checkingMoves;
		copyTable->pieces.back()->isChecking = piece->isChecking;
		copyTable->SetOnTable(copyTable->pieces.back(), copyTable->pieces.back()->tablePosition);

		if (activePiece->tablePosition == piece->tablePosition)
		{
			copyTable->activePiece = copyTable->pieces.back();
		}

		copyTable->enPassantPosition[0] = this->enPassantPosition[0];
		copyTable->enPassantPosition[1] = this->enPassantPosition[1];
	}

	

	return copyTable;
}

bool Table::CheckForCheck(const bool _playerOneTurn, Square* _squareToMove)
{
	bool tempCheck = false;
	if (_playerOneTurn)
	{
		tempCheck = check[0];
	}
	else
	{
		tempCheck = check[1];
	}

	//This is created so we can restore the ActivePiece's current square easily
	Square* tempSquareActivePiece = nullptr;
	//tempSquareActivePiece = (Square*)malloc(sizeof(Square));
	
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (board[x][y]->onSquare == activePiece)
			{
				//memcpy(tempSquareActivePiece, board[x][y], sizeof(Square));
				tempSquareActivePiece = new Square(board[x][y]->isWhite, board[x][y]->tablePosition.x, board[x][y]->tablePosition.y);
				tempSquareActivePiece->onSquare = board[x][y]->onSquare;
			}
		}
	}
	
	//This is created for the square were we might eat a piece during the check
	Square* tempSquareEatenPiece = nullptr;

	if (_squareToMove->onSquare != nullptr)
	{
		//tempSquareEatenPiece = (Square*)malloc(sizeof(Square));

		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if (board[x][y]->onSquare == activePiece)
				{
					//memcpy(tempSquareEatenPiece, board[x][y], sizeof(Square));
					tempSquareEatenPiece = new Square(board[x][y]->isWhite, board[x][y]->tablePosition.x, board[x][y]->tablePosition.y);
					tempSquareEatenPiece->onSquare = board[x][y]->onSquare;
				}
			}
		}
	}
	else
	{
		delete tempSquareEatenPiece;
	}
		
	//We use these tempPieces to revert the pieces to their original states
	ChessPiece* tempPieceActive = nullptr;
	ChessPiece* tempPieceEaten = nullptr;

	if (_squareToMove->onSquare == nullptr)
	{
		delete tempPieceEaten;
	}
	else
	{
		tempPieceEaten = new ChessPiece(_squareToMove->onSquare->type, _squareToMove->onSquare->player);

		tempPieceEaten->allMoves = _squareToMove->onSquare->allMoves;
		tempPieceEaten->checkingMoves = _squareToMove->onSquare->checkingMoves;
		tempPieceEaten->isChecking = _squareToMove->onSquare->isChecking;
		tempPieceEaten->lastPosition = _squareToMove->onSquare->lastPosition;
		tempPieceEaten->possibleMoves = _squareToMove->onSquare->possibleMoves;
		tempPieceEaten->tablePosition = _squareToMove->onSquare->tablePosition;
	}

	tempPieceActive = new ChessPiece(activePiece->type, activePiece->player);
	tempPieceActive->allMoves = activePiece->allMoves;
	tempPieceActive->checkingMoves = activePiece->checkingMoves;
	tempPieceActive->isChecking = activePiece->isChecking;
	tempPieceActive->lastPosition = activePiece->lastPosition;
	tempPieceActive->possibleMoves = activePiece->possibleMoves;
	tempPieceActive->tablePosition = activePiece->tablePosition;

	/*
	*If there is an enemy piece, we need to create another temp piecce for that as well.
	*That one will be used if there was a piece on a position  where the active player moved his piece.
	*Later on this piece can be restored with the temp piece we created.
	*/


	//first we need to make sure that by moving the active player doesn't allow it's king to get checked
	if (_squareToMove->onSquare != nullptr)
	{
		//make the square active player is right now null
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if (board[x][y]->onSquare == activePiece)
				{
					board[x][y]->onSquare = nullptr;					
				}
			}
		}

		//remove the piece that was on _squareToMove
		EatPiece(_squareToMove->onSquare);
		_squareToMove->onSquare = nullptr;

		//next move the activePiece
		_squareToMove->onSquare = activePiece;
		activePiece->tablePosition = _squareToMove->tablePosition;
		
		//check if the active player is now being checked
		std::vector<ChessPiece*>::iterator piece = pieces.begin();

		for (; piece != pieces.end(); piece++)
		{
			CalculatePieceMovement((*piece));
		}
		
		//we need to push this piece into the pieces since we deleted the original one
		pieces.push_back(tempPieceEaten);		

		//revert all movement
		bool found = false;

		//first we set the current activePiece's position as the position of the original piece
		for (int x = 0; x < 8; x++)
		{
			if (found)
			{
				break;
			}

			for (int y = 0; y < 8; y++)
			{
				if (found)
				{
					break;
				}

				if (board[x][y]->onSquare == activePiece)
				{
					board[x][y]->onSquare = tempPieceEaten;
					found = true;
				}
			}
		}

		//move the active piece back into its original position		

		found = false;

		for (int x = 0; x < 8; x++)
		{
			if (found)
			{
				break;
			}

			for (int y = 0; y < 8; y++)
			{
				if (found)
				{
					break;
				}

				if (board[x][y]->tablePosition == tempSquareActivePiece->tablePosition)
				{
					board[x][y]->onSquare = activePiece;
					activePiece->tablePosition = board[x][y]->tablePosition;
					found = true;
				}
			}
		}

		//if the active player is being checked, don't allow the move
		if ((_playerOneTurn && check[0]) || !_playerOneTurn && check[1])
		{
			//revert the check back to not being in check
			if (_playerOneTurn)
			{
				check[0] = tempCheck;

			}
			else
			{
				check[1] = tempCheck;
			}

			return true;
		}
		//otherwise allow the move
		else
		{
			//revert the check back to not being in check
			if (_playerOneTurn)
			{
				check[0] = tempCheck;

			}
			else
			{
				check[1] = tempCheck;
			}

			return false;
		}
	}

	else
	{
		//since there was no need for the temp piece for eaten piece we can delete the pointer
		delete tempPieceEaten;

		//make the square active player is right now null
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if (board[x][y]->onSquare == activePiece)
				{
					board[x][y]->onSquare = nullptr;
				}
			}
		}

		//next move the activePiece
		_squareToMove->onSquare = activePiece;
		activePiece->tablePosition = _squareToMove->tablePosition;

		//check if the active player is now being checked
		std::vector<ChessPiece*>::iterator piece = pieces.begin();

		for (; piece != pieces.end(); piece++)
		{
			CalculatePieceMovement((*piece));
		}

		//revert all movement
		bool found = false;

		//first we set the current activePiece's position as the position of the original piece
		for (int x = 0; x < 8; x++)
		{
			if (found)
			{
				break;
			}

			for (int y = 0; y < 8; y++)
			{
				if (found)
				{
					break;
				}

				if (board[x][y]->onSquare == activePiece)
				{
					board[x][y]->onSquare = tempPieceEaten;
					found = true;
				}
			}
		}

		found = false;

		//move the active piece back into its original position		
		for (int x = 0; x < 8; x++)
		{
			if (found)
			{
				break;
			}

			for (int y = 0; y < 8; y++)
			{
				if (found)
				{
					break;
				}

				if (board[x][y]->tablePosition == tempSquareActivePiece->tablePosition)
				{
					board[x][y]->onSquare = activePiece;
					activePiece->tablePosition = board[x][y]->tablePosition;
					found = true;
				}
			}
		}

		//if the active player is being checked, don't allow the move
		if ((_playerOneTurn && check[0]) || !_playerOneTurn && check[1])
		{
			//calculate the moves once more so that the game doesn't show wrong possible moves
			std::vector<ChessPiece*>::iterator piece = pieces.begin();

			for (; piece != pieces.end(); piece++)
			{
				CalculatePieceMovement((*piece));
			}

			//revert the check back to not being in check
			if (_playerOneTurn)
			{
				check[0] = tempCheck;

			}
			else
			{
				check[1] = tempCheck;
			}

			//return true because player is in check
			return true;
		}
		//otherwise allow the move
		else
		{
			//calculate the moves once more so that the game doesn't show wrong possible moves
			std::vector<ChessPiece*>::iterator piece = pieces.begin();

			for (; piece != pieces.end(); piece++)
			{
				CalculatePieceMovement((*piece));
			}

			//revert the check back to not being in check
			if (_playerOneTurn)
			{
				check[0] = tempCheck;

			}
			else
			{
				check[1] = tempCheck;
			}

			//return false since the player is not in check
			return false;
		}
	}
}

bool Table::MoveActivePiece(const bool _playerOneTurn, Square* _squareToMove)
{
	if (activePiece)
	{
		if (!CheckForCheck(_playerOneTurn, _squareToMove))
		{
			if (_squareToMove->onSquare != nullptr)
			{
				EatPiece(_squareToMove->onSquare);
			}

			//update where active piece has moved so far
			activePiece->allMoves.push_back(std::make_pair(activePiece->tablePosition, _squareToMove->tablePosition));

			//update en passant position
			if (activePiece->type == ChessPieceType::pawn)
			{
				//if player uses En passant maneuver, eat the pawn which left it's back unguarded
				if (_squareToMove->tablePosition.x == enPassantPosition[0] && _squareToMove->tablePosition.y == enPassantPosition[1])
				{
					if (activePiece->player == 1)
					{
						if (board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y + 1]->onSquare != nullptr)
						{
							EatPiece(board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y + 1]->onSquare);
							board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y + 1]->onSquare = nullptr;
							enPassantPosition[0] = -12;
							enPassantPosition[1] = -12;
						}
					}
					else if (activePiece->player == 2)
					{
						if (board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y - 1])
						{
							EatPiece(board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y - 1]->onSquare);
							board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y - 1]->onSquare = nullptr;
							enPassantPosition[0] = -12;
							enPassantPosition[1] = -12;
						}
					}
				}

				//update En passant position
				if (activePiece->tablePosition.y - _squareToMove->tablePosition.y == 2)
				{
					enPassantPosition[0] = _squareToMove->tablePosition.x;
					enPassantPosition[1] = _squareToMove->tablePosition.y + 1;
				}
				else if (activePiece->tablePosition.y - _squareToMove->tablePosition.y == -2)
				{
					enPassantPosition[0] = _squareToMove->tablePosition.x;
					enPassantPosition[1] = _squareToMove->tablePosition.y - 1;
				}
				else
				{
					if ((enPassantPosition[0] >= 0 && enPassantPosition[0] < 8) && (enPassantPosition[1] >= 0 && enPassantPosition[1] < 8))
					{
						enPassantPosition[0] = -12;
						enPassantPosition[1] = -12;
					}
				}

			}

			//check if the pawn gets to promote itself to a queen
			if (activePiece->type == ChessPieceType::pawn && (_squareToMove->tablePosition.y == 0 || _squareToMove->tablePosition.y == 7))
			{
				pieces.push_back(new ChessPiece(ChessPieceType::queen, activePiece->player));
				pieces.back()->tablePosition = sf::Vector2i(activePiece->tablePosition.x, activePiece->tablePosition.y);

				std::vector<ChessPiece*>::iterator piece = pieces.begin();
				for (; piece != pieces.end(); piece++)
				{
					if ((*piece) == activePiece)
					{
						delete (*piece);
						pieces.erase(piece);
						break;
					}
				}

				activePiece = pieces.back();
			}

			if (activePiece->type != ChessPieceType::pawn)
			{
				enPassantPosition[0] = -12;
				enPassantPosition[1] = -12;
			}

			SetOnTable(activePiece, _squareToMove);
			//UpdateCheck();
			ClearActivePiece();
			return true;
		}
	}
	else
	{
		return false;
	}
}

void Table::EatPiece(ChessPiece* pieceToDelete)
{
	std::vector<ChessPiece*>::iterator piece = pieces.begin();

	while (piece != pieces.end())
	{
		if ((*piece) == pieceToDelete)
		{
			delete(*piece);
			piece = pieces.erase(piece);
			break;
		}
		piece++;
	}
}

ChessPiece* Table::GetPieceAtPosition(const std::array<int, 2> _position)
{
	for each (ChessPiece* piece in pieces)
	{
		if (piece->tablePosition.x == _position[0] && piece->tablePosition.y == _position[1])
		{
			return piece;
		}
	}

	return nullptr;
}

void Table::SetOnTable(ChessPiece* _piece, sf::Vector2i _position)
{
	board[_piece->tablePosition.x][_piece->tablePosition.y]->onSquare = nullptr;
	_piece->tablePosition = _position;
	_piece->GetSprite().setPosition((board[_piece->tablePosition.x][_piece->tablePosition.y]->sprite.getPosition().x), (board[_piece->tablePosition.x][_piece->tablePosition.y]->sprite.getPosition().y));
	board[_position.x][_position.y]->onSquare = _piece;
}

void Table::SetOnTable(ChessPiece* _piece, Square* _square)
{
	board[_piece->tablePosition.x][_piece->tablePosition.y]->onSquare = nullptr;
	_piece->tablePosition = _square->tablePosition;
	_piece->GetSprite().setPosition((board[_piece->tablePosition.x][_piece->tablePosition.y]->sprite.getPosition().x), (board[_piece->tablePosition.x][_piece->tablePosition.y]->sprite.getPosition().y));
	board[_piece->tablePosition.x][_piece->tablePosition.y]->onSquare = _piece;
}

Square* Table::GetSquareAtPosition(sf::Vector2i position)
{
	return board[position.x][position.y];
}

bool Table::CalculatePieceMovement(ChessPiece* piece)
{	
	piece->possibleMoves.clear();

	switch (piece->type)
	{
	case ChessPieceType::pawn:
	{
		if (piece->player == 1)
		{
			//check if there is a piece in front of the pawn
			//if yes, don't allow movement
			bool allowMovementForward = true;

			if (piece->tablePosition.y - 1 > -1)
			{
				for each (ChessPiece* otherPiece in pieces)
				{
					if ((otherPiece->tablePosition.x == piece->tablePosition.x) && (otherPiece->tablePosition.y == piece->tablePosition.y - 1))
					{
						allowMovementForward = false;
					}
				}
			}

			if (allowMovementForward)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y - 1));
				
				if (piece->allMoves.empty())
				{
					bool allowTwoSquareMovent = true;

					for each (ChessPiece* otherPiece in pieces)
					{
						if ((otherPiece->tablePosition.x == piece->tablePosition.x) && (otherPiece->tablePosition.y == piece->tablePosition.y - 2))
						{
							allowTwoSquareMovent = false;
						}
					}

					if (allowTwoSquareMovent)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y - 2));
					}
				}
			}

			//Eat left
			if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y - 1 > -1)
			{
				if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 1]->onSquare != nullptr)
				{
					if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 1]->onSquare->player != piece->player)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 1));

						if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 1]->onSquare->type == ChessPieceType::king)
						{
							check[1] = true;
							piece->isChecking = true;
						}
					}
				}
			}

			//Eat right
			if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y - 1 > -1)
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare != nullptr)
				{
					if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare->player != piece->player)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 1));

						if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare->type == ChessPieceType::king)
						{
							check[1] = true;
							piece->isChecking = true;
						}
					}
				}
			}

			//Check En passant maneuver left
			if (enPassantPosition[0] > -1 && enPassantPosition[1] > -1)
			{
				if (enPassantPosition[0] == piece->tablePosition.x - 1 && piece->tablePosition.y - 1 == enPassantPosition[1])
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 1));
				}
			}

			//Check En passant maneuver right
			if (enPassantPosition[0] > +1 && enPassantPosition[1] > -1)
			{
				if (enPassantPosition[0] == piece->tablePosition.x + 1 && piece->tablePosition.y - 1 == enPassantPosition[1])
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 1));
				}
			}

		}
		else if (piece->player == 2)
		{
			//check if there is a piece in front of the pawn
			//if yes, don't allow movement
			bool allowMovementForward = true;

			for each (ChessPiece* otherPiece in pieces)
			{
				if ((otherPiece->tablePosition.x == piece->tablePosition.x) && (otherPiece->tablePosition.y == piece->tablePosition.y + 1))
				{
					allowMovementForward = false;
				}
			}

			if (piece->tablePosition.y + 1 < 8 && allowMovementForward)
			{
				//highlight the available square
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y + 1));
				//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y + 1]);

				if (piece->allMoves.empty())
				{
					bool allowTwoSquareMovement = true;

					for each (ChessPiece* otherPiece in pieces)
					{
						if ((otherPiece->tablePosition.x == piece->tablePosition.x) && (otherPiece->tablePosition.y == piece->tablePosition.y + 2))
						{
							allowTwoSquareMovement = false;
						}
					}

					if (allowTwoSquareMovement)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y + 2));
						//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y + 2]);
					}
				}
			}

			//Eat left
			if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y + 1 < 8)
			{
				if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare != nullptr)
				{
					if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare->player != piece->player)
					{
						if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare->type == ChessPieceType::king)
						{
							check[0] = true;
							piece->isChecking = true;
						}
						else
						{
							piece->isChecking = false;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 1));
						//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y + 1]);
					}
				}
			}

			//Eat right
			if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y + 1 < 8)
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare != nullptr)
				{
					if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare->player != piece->player)
					{
						if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare->type == ChessPieceType::king)
						{
							check[0] = true;
							piece->isChecking = true;
						}
						else
						{
							piece->isChecking = false;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 1));
						//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y - 1]);
					}
				}
			}

			//Check En passant maneuver left
			if (enPassantPosition[0] > -1 && enPassantPosition[1] > +1)
			{
				if (enPassantPosition[0] == piece->tablePosition.x - 1 && piece->tablePosition.y + 1 == enPassantPosition[1])
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 1));
				}
			}

			//Check En passant maneuver right
			if (enPassantPosition[0] > +1 && enPassantPosition[1] > +1)
			{
				if (enPassantPosition[0] == piece->tablePosition.x + 1 && piece->tablePosition.y + 1 == enPassantPosition[1])
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 1));
				}
			}
		}


		break;
	}
	case ChessPieceType::knight:
	{

		if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y - 2 > -1)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 2]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 2));

			else if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 2]->onSquare->player != piece->player)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 2));

				if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 2]->onSquare->type == ChessPieceType::king)
				{
					piece->isChecking = true;
					check[board[piece->tablePosition.x - 1][piece->tablePosition.y - 2]->onSquare->player - 1] = true;
				}
			}
			//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y - 2]);
		}

		if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y - 2 > -1)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 2]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 2));

			else if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 2]->onSquare->player != piece->player)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 2));

				if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 2]->onSquare->type == ChessPieceType::king)
				{
					piece->isChecking = true;
					check[board[piece->tablePosition.x + 1][piece->tablePosition.y - 2]->onSquare->player - 1] = true;
				}
			}
			//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y - 2]);
		}

		if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y + 2 < 8)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 2]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 2));

			else if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 2]->onSquare->player != piece->player)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 2));

				if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 2]->onSquare->type == ChessPieceType::king)
				{
					piece->isChecking = true;
					check[board[piece->tablePosition.x - 1][piece->tablePosition.y + 2]->onSquare->player - 1] = true;
				}
			}
			//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y + 2]);
		}

		if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y + 2 < 8)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 2]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 2));

			else if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 2]->onSquare->player != piece->player)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 2));

				if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 2]->onSquare->type == ChessPieceType::king)
				{
					piece->isChecking = true;
					check[board[piece->tablePosition.x + 1][piece->tablePosition.y + 2]->onSquare->player - 1] = true;
				}
			}

			//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y + 2]);
		}

		if (piece->tablePosition.x + 2 < 8 && piece->tablePosition.y - 1 > -1)
		{
			if (board[piece->tablePosition.x + 2][piece->tablePosition.y - 1]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 2, piece->tablePosition.y - 1));

			else if (board[piece->tablePosition.x + 2][piece->tablePosition.y - 1]->onSquare->player != piece->player)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 2, piece->tablePosition.y - 1));

				if (board[piece->tablePosition.x + 2][piece->tablePosition.y - 1]->onSquare->type == ChessPieceType::king)
				{
					piece->isChecking = true;
					check[board[piece->tablePosition.x + 2][piece->tablePosition.y - 1]->onSquare->player - 1] = true;
				}
			}

			//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 2][activePiece->tablePosition.y - 1]);
		}

		if (piece->tablePosition.x + 2 < 8 && piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x + 2][piece->tablePosition.y + 1]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 2, piece->tablePosition.y + 1));

			else if (board[piece->tablePosition.x + 2][piece->tablePosition.y + 1]->onSquare->player != piece->player)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 2, piece->tablePosition.y + 1));

				if (board[piece->tablePosition.x + 2][piece->tablePosition.y + 1]->onSquare->type == ChessPieceType::king)
				{
					piece->isChecking = true;
					check[board[piece->tablePosition.x + 2][piece->tablePosition.y + 1]->onSquare->player - 1] = true;
				}
			}

			//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 2][activePiece->tablePosition.y + 1]);
		}

		if (piece->tablePosition.x - 2 > -1 && piece->tablePosition.y - 1 > -1)
		{
			if (board[piece->tablePosition.x - 2][piece->tablePosition.y - 1]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 2, piece->tablePosition.y - 1));

			else if (board[piece->tablePosition.x - 2][piece->tablePosition.y - 1]->onSquare->player != piece->player)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 2, piece->tablePosition.y - 1));

				if (board[piece->tablePosition.x - 2][piece->tablePosition.y - 1]->onSquare->type == ChessPieceType::king)
				{
					piece->isChecking = true;
					check[board[piece->tablePosition.x - 2][piece->tablePosition.y - 1]->onSquare->player - 1] = true;
				}
			}

			//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 2][activePiece->tablePosition.y - 1]);
		}

		if (piece->tablePosition.x - 2 > -1 && piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x - 2][piece->tablePosition.y + 1]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 2, piece->tablePosition.y + 1));

			else if (board[piece->tablePosition.x - 2][piece->tablePosition.y + 1]->onSquare->player != piece->player)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 2, piece->tablePosition.y + 1));

				if (board[piece->tablePosition.x - 2][piece->tablePosition.y + 1]->onSquare->type == ChessPieceType::king)
				{
					piece->isChecking = true;
					check[board[piece->tablePosition.x - 2][piece->tablePosition.y + 1]->onSquare->player - 1] = true;
				}
			}

			//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 2][activePiece->tablePosition.y - 1]);
		}
		break;
	}
	case ChessPieceType::rook:
	{
		//towards top
		for (int i = piece->tablePosition.y - 1; i > -1; i--)
		{
			if (board[piece->tablePosition.x][i]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
				//squaresToBeHighlighted.push_back(board[piece->tablePosition.x][i]);
			}
			else
			{
				if (board[piece->tablePosition.x][i]->onSquare->player != piece->player)
				{
					if (board[piece->tablePosition.x][i]->onSquare->type == ChessPieceType::king)
					{
						piece->isChecking = true;
						check[board[piece->tablePosition.x][i]->onSquare->player - 1] = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x][i]);
				}
				break;
			}
		}

		//towards bottom
		for (int i = piece->tablePosition.y + 1; i < 8; i++)
		{
			if (board[piece->tablePosition.x][i]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
				//squaresToBeHighlighted.push_back(board[piece->tablePosition.x][i]);
			}
			else
			{
				if (board[piece->tablePosition.x][i]->onSquare->player != piece->player)
				{
					if (board[piece->tablePosition.x][i]->onSquare->type == ChessPieceType::king)
					{
						piece->isChecking = true;
						check[board[piece->tablePosition.x][i]->onSquare->player - 1] = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x][i]);
				}
				break;
			}
		}

		//towards left
		for (int i = piece->tablePosition.x - 1; i > -1; i--)
		{
			if (board[i][piece->tablePosition.y]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
				//squaresToBeHighlighted.push_back(board[i][piece->tablePosition.y]);
			}
			else
			{
				if (board[i][piece->tablePosition.y]->onSquare->player != piece->player)
				{
					if (board[i][piece->tablePosition.y]->onSquare->type == ChessPieceType::king)
					{
						piece->isChecking = true;
						check[board[i][piece->tablePosition.y]->onSquare->player - 1] = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
					//squaresToBeHighlighted.push_back(board[i][piece->tablePosition.y]);
				}
				break;
			}
		}

		//towards right
		for (int i = piece->tablePosition.x + 1; i < 8; i++)
		{
			if (board[i][piece->tablePosition.y]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
				//squaresToBeHighlighted.push_back(board[i][piece->tablePosition.y]);
			}
			else
			{
				if (board[i][piece->tablePosition.y]->onSquare->player != piece->player)
				{
					if (board[i][piece->tablePosition.y]->onSquare->type == ChessPieceType::king)
					{
						piece->isChecking = true;
						check[board[i][piece->tablePosition.y]->onSquare->player - 1] = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
					//squaresToBeHighlighted.push_back(board[i][piece->tablePosition.y]);
				}
				break;
			}
		}
		break;
	}
	case ChessPieceType::bishop:
	{
		int x = 1;
		int y = 1;

		//bottom right
		while (piece->tablePosition.x + x < 8 && piece->tablePosition.y + y < 8)
		{
			if (board[piece->tablePosition.x + x][piece->tablePosition.y + y] != nullptr)
			{
				if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare == nullptr)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y + y));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x + x][piece->tablePosition.y + y]);
				}
				else
				{
					if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->player != piece->player)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y + y));

						if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->type == ChessPieceType::king)
						{
							piece->isChecking = true;
							check[board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->player - 1] = true;
						}

						//squaresToBeHighlighted.push_back(board[piece->tablePosition.x + x][piece->tablePosition.y + y]);
					}
					break;
				}
			}
			else
			{
				break;
			}

			x++;
			y++;
		}

		//bottom left
		x = 1;
		y = 1;

		while (piece->tablePosition.x - x > -1 && piece->tablePosition.y + y < 8)
		{
			if (board[piece->tablePosition.x - x][piece->tablePosition.y + y] != nullptr)
			{
				if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare == nullptr)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y + y));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x - x][piece->tablePosition.y + y]);
				}
				else
				{
					if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->player != piece->player)
					{
						if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->type == ChessPieceType::king)
						{
							piece->isChecking = true;
							check[board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->player - 1] = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y + y));
						//squaresToBeHighlighted.push_back(board[piece->tablePosition.x - x][piece->tablePosition.y + y]);
					}
					break;
				}
			}
			else
			{
				break;
			}

			x++;
			y++;
		}

		//top right
		x = 1;
		y = 1;

		while (piece->tablePosition.x + x < 8 && piece->tablePosition.y - y > -1)
		{
			if (board[piece->tablePosition.x + x][piece->tablePosition.y - y] != nullptr)
			{
				if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare == nullptr)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y - y));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x + x][piece->tablePosition.y - y]);
				}
				else
				{
					if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->player != piece->player)
					{
						if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->type == ChessPieceType::king)
						{
							piece->isChecking = true;
							check[board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->player - 1] = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y - y));
						//squaresToBeHighlighted.push_back(board[piece->tablePosition.x + x][piece->tablePosition.y - y]);
					}
					break;
				}
			}
			else
			{
				break;
			}

			x++;
			y++;
		}

		//top left
		x = 1;
		y = 1;

		while (piece->tablePosition.x - x > -1 && piece->tablePosition.y - y > -1)
		{
			if (board[piece->tablePosition.x - x][piece->tablePosition.y - y] != nullptr)
			{
				if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare == nullptr)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y - y));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x - x][piece->tablePosition.y - y]);
				}
				else
				{
					if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->player != piece->player)
					{
						if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->type == ChessPieceType::king)
						{
							piece->isChecking = true;
							check[board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->player - 1] = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y - y));
						//squaresToBeHighlighted.push_back(board[piece->tablePosition.x - x][piece->tablePosition.y - y]);
					}
					break;
				}
			}
			else
			{
				break;
			}

			x++;
			y++;
		}
		break;
	}
	case ChessPieceType::queen:
	{
		//towards top
		for (int i = piece->tablePosition.y - 1; i > -1; i--)
		{
			if (board[piece->tablePosition.x][i]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
				//squaresToBeHighlighted.push_back(board[piece->tablePosition.x][i]);
			}
			else
			{
				if (board[piece->tablePosition.x][i]->onSquare->player != piece->player)
				{
					if (board[piece->tablePosition.x][i]->onSquare->type == ChessPieceType::king)
					{
						piece->isChecking = true;
						check[board[piece->tablePosition.x][i]->onSquare->player - 1] = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x][i]);
				}
				break;
			}
		}

		//towards bottom
		for (int i = piece->tablePosition.y + 1; i < 8; i++)
		{
			if (board[piece->tablePosition.x][i]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
				//squaresToBeHighlighted.push_back(board[piece->tablePosition.x][i]);
			}
			else
			{
				if (board[piece->tablePosition.x][i]->onSquare->player != piece->player)
				{
					if (board[piece->tablePosition.x][i]->onSquare->type == ChessPieceType::king)
					{
						piece->isChecking = true;
						check[board[piece->tablePosition.x][i]->onSquare->player - 1] = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x][i]);
				}
				break;
			}
		}

		//towards left
		for (int i = piece->tablePosition.x - 1; i > -1; i--)
		{
			if (board[i][piece->tablePosition.y]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
				//squaresToBeHighlighted.push_back(board[i][piece->tablePosition.y]);
			}
			else
			{
				if (board[i][piece->tablePosition.y]->onSquare->player != piece->player)
				{
					if (board[i][piece->tablePosition.y]->onSquare->type == ChessPieceType::king)
					{
						piece->isChecking = true;
						check[board[i][piece->tablePosition.y]->onSquare->player - 1] = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
					//squaresToBeHighlighted.push_back(board[i][piece->tablePosition.y]);
				}
				break;
			}
		}

		//towards right
		for (int i = piece->tablePosition.x + 1; i < 8; i++)
		{
			if (board[i][piece->tablePosition.y]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
				//squaresToBeHighlighted.push_back(board[i][piece->tablePosition.y]);
			}
			else
			{
				if (board[i][piece->tablePosition.y]->onSquare->player != piece->player)
				{
					if (board[i][piece->tablePosition.y]->onSquare->type == ChessPieceType::king)
					{
						piece->isChecking = true;
						check[board[i][piece->tablePosition.y]->onSquare->player - 1] = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
					//squaresToBeHighlighted.push_back(board[i][piece->tablePosition.y]);
				}
				break;
			}
		}

		int x = 1;
		int y = 1;

		//bottom right
		while (piece->tablePosition.x + x < 8 && piece->tablePosition.y + y < 8)
		{
			if (board[piece->tablePosition.x + x][piece->tablePosition.y + y] != nullptr)
			{
				if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare == nullptr)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y + y));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x + x][piece->tablePosition.y + y]);
				}
				else
				{
					if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->player != piece->player)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y + y));

						if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->type == ChessPieceType::king)
						{
							piece->isChecking = true;
							check[board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->player - 1] = true;
						}

						//squaresToBeHighlighted.push_back(board[piece->tablePosition.x + x][piece->tablePosition.y + y]);
					}
					break;
				}
			}
			else
			{
				break;
			}

			x++;
			y++;
		}

		//bottom left
		x = 1;
		y = 1;

		while (piece->tablePosition.x - x > -1 && piece->tablePosition.y + y < 8)
		{
			if (board[piece->tablePosition.x - x][piece->tablePosition.y + y] != nullptr)
			{
				if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare == nullptr)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y + y));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x - x][piece->tablePosition.y + y]);
				}
				else
				{
					if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->player != piece->player)
					{
						if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->type == ChessPieceType::king)
						{
							piece->isChecking = true;
							check[board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->player - 1] = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y + y));
						//squaresToBeHighlighted.push_back(board[piece->tablePosition.x - x][piece->tablePosition.y + y]);
					}
					break;
				}
			}
			else
			{
				break;
			}

			x++;
			y++;
		}

		//top right
		x = 1;
		y = 1;

		while (piece->tablePosition.x + x < 8 && piece->tablePosition.y - y > -1)
		{
			if (board[piece->tablePosition.x + x][piece->tablePosition.y - y] != nullptr)
			{
				if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare == nullptr)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y - y));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x + x][piece->tablePosition.y - y]);
				}
				else
				{
					if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->player != piece->player)
					{
						if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->type == ChessPieceType::king)
						{
							piece->isChecking = true;
							check[board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->player - 1] = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y - y));
						//squaresToBeHighlighted.push_back(board[piece->tablePosition.x + x][piece->tablePosition.y - y]);
					}
					break;
				}
			}
			else
			{
				break;
			}

			x++;
			y++;
		}

		//top left
		x = 1;
		y = 1;

		while (piece->tablePosition.x - x > -1 && piece->tablePosition.y - y > -1)
		{
			if (board[piece->tablePosition.x - x][piece->tablePosition.y - y] != nullptr)
			{
				if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare == nullptr)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y - y));
					//squaresToBeHighlighted.push_back(board[piece->tablePosition.x - x][piece->tablePosition.y - y]);
				}
				else
				{
					if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->player != piece->player)
					{
						if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->type == ChessPieceType::king)
						{
							piece->isChecking = true;
							check[board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->player - 1] = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y - y));
						//squaresToBeHighlighted.push_back(board[piece->tablePosition.x - x][piece->tablePosition.y - y]);
					}
					break;
				}
			}
			else
			{
				break;
			}

			x++;
			y++;
		}
		break;
	}
	case ChessPieceType::king:
	{
		//top
		if (piece->tablePosition.y - 1 > -1)
		{
			if (board[piece->tablePosition.x][piece->tablePosition.y - 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y - 1));
				//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y - 1]);
			}
			else
			{
				if (board[piece->tablePosition.x][piece->tablePosition.y - 1]->onSquare->player != piece->player)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y - 1));
					//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y - 1]);
				}
			}
		}

		//bottom
		if (piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x][piece->tablePosition.y + 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y + 1));
				//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y + 1]);
			}
			else
			{
				if (board[piece->tablePosition.x][piece->tablePosition.y + 1]->onSquare->player != piece->player)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y + 1));
					//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x][activePiece->tablePosition.y + 1]);
				}
			}
		}

		//left
		if (piece->tablePosition.x - 1 > -1)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y));
				//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y]);
			}
			else
			{
				if (board[piece->tablePosition.x - 1][piece->tablePosition.y]->onSquare->player != piece->player)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y));
					//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y]);
				}
			}
		}

		//right
		if (piece->tablePosition.x + 1 < 8)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y));
				//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y]);
			}
			else
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y]->onSquare->player != piece->player)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y));
					//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y]);
				}
			}
		}

		//upper left
		if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y - 1 > -1)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 1));
				//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y - 1]);
			}
			else
			{
				if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 1]->onSquare->player != piece->player)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 1));
					//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y - 1]);
				}
			}
		}

		//upper right
		if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y - 1 > -1)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 1));
				//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y - 1]);
			}
			else
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare->player != piece->player)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 1));
					//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y - 1]);
				}
			}
		}

		//lower right
		if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 1));
				//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y + 1]);
			}
			else
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare->player != piece->player)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 1));
					//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x + 1][activePiece->tablePosition.y + 1]);
				}
			}
		}

		//lower left
		if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 1));
				//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y + 1]);
			}
			else
			{
				if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare->player != piece->player)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 1));
					//squaresToBeHighlighted.push_back(board[activePiece->tablePosition.x - 1][activePiece->tablePosition.y + 1]);
				}
			}
		}

		break;
	}
	default:
		break;
	}	
	return true;
}


void Table::CalculatePieceMovementForEachPiece()
{
	std::vector<ChessPiece*>::iterator piece = pieces.begin();

	for (; piece != pieces.end(); piece++)
	{
		CalculatePieceMovement((*piece));
	}
}

//bool Table::CheckForCheckmate()
//{
//	for (std::vector<ChessPiece*>::iterator piece = pieces.begin(); piece != pieces.end(); piece++)
//	{
//		if ((*piece)->type == ChessPieceType::king)
//		{
//
//		}
//	}
//}

void Table::Deselect()
{
	ClearHighlights();
	ClearActivePiece();
}

void Table::DebugStuff()
{
	//int debug[8][8] = {0};

	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		if (board[i][j]->onSquare != nullptr)
	//		{
	//			debug[i][j] = 1;
	//		}
	//		else
	//		{
	//			debug[i][j] = 2;
	//		}				
	//	}
	//}

	system("cls");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[j][i]->onSquare != nullptr)
			{
				printf("X");
			}
			else if (board[j][i]->onSquare == nullptr)
			{
				printf(".");
			}
		}
		printf("\n");
	}

	printf("En passant position \n");
	printf("x: %d\n y: %d", enPassantPosition[0], enPassantPosition[1]);

	printf("\nCheck Status:\n");
	printf("player 1: %d\nplayer 2: %d", check[0], check[1]);
}