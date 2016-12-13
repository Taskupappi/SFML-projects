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

	checkmate[0] = false;
	checkmate[1] = false;
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

void Table::Initialize(Player _players[2])
{
	//player 1 pieces
	for (int i = 0; i < 8; i++)
	{
		//rooks
		if (i == 0 || i == 7)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::rook, _players[0]));
			pieces.back()->tablePosition = sf::Vector2i(i, 7);
		}
		//knights
		else if (i == 1 || i == 6)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::knight, _players[0]));
			pieces.back()->tablePosition = sf::Vector2i(i, 7);
		}
		//bishops
		else if (i == 2 || i == 5)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::bishop, _players[0]));
			pieces.back()->tablePosition = sf::Vector2i(i, 7);
		}
		//Queen
		else if (i == 3)
		{
			if (_players[0].color == COLOR::WHITE)
			{
				pieces.push_back(new ChessPiece(ChessPieceType::queen, _players[0]));
				pieces.back()->tablePosition = sf::Vector2i(i, 7);
			}
			else
			{
				pieces.push_back(new ChessPiece(ChessPieceType::queen, _players[0]));
				pieces.back()->tablePosition = sf::Vector2i((i + 1), 7);
			}
		}
		//King
		else if (i == 4)
		{
			if (_players[0].color == COLOR::WHITE)
			{
				pieces.push_back(new ChessPiece(ChessPieceType::king, _players[0]));
				pieces.back()->tablePosition = sf::Vector2i(i, 7);
			}
			else
			{
				pieces.push_back(new ChessPiece(ChessPieceType::king, _players[0]));
				pieces.back()->tablePosition = sf::Vector2i((i - 1), 7);
			}
		}
	}

	for (int x = 0; x < 8; x++)
	{
		//pawns
		pieces.push_back(new ChessPiece(ChessPieceType::pawn, _players[0]));
		pieces.back()->tablePosition = sf::Vector2i(x, 6);
	}

	//player 2 pieces
	for (int i = 0; i < 8; i++)
	{
		//rooks
		if (i == 0 || i == 7)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::rook, _players[1]));
			pieces.back()->tablePosition = sf::Vector2i(i, 0);
		}
		//knights
		else if (i == 1 || i == 6)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::knight, _players[1]));
			pieces.back()->tablePosition = sf::Vector2i(i, 0);
		}
		//bishops
		else if (i == 2 || i == 5)
		{
			pieces.push_back(new ChessPiece(ChessPieceType::bishop, _players[1]));
			pieces.back()->tablePosition = sf::Vector2i(i, 0);
		}
		//Queen
		else if (i == 3)
		{
			if (_players[0].color == COLOR::WHITE)
			{
				pieces.push_back(new ChessPiece(ChessPieceType::queen, _players[1]));
				pieces.back()->tablePosition = sf::Vector2i(i, 0);
			}
			else
			{
				pieces.push_back(new ChessPiece(ChessPieceType::queen, _players[1]));
				pieces.back()->tablePosition = sf::Vector2i((i + 1), 0);
			}
		
		}
		//King
		else if (i == 4)
		{
			if (_players[0].color == COLOR::WHITE)
			{
				pieces.push_back(new ChessPiece(ChessPieceType::king, _players[1]));
				pieces.back()->tablePosition = sf::Vector2i(i, 0);
			}
			else
			{
				pieces.push_back(new ChessPiece(ChessPieceType::king, _players[1]));
				pieces.back()->tablePosition = sf::Vector2i((i - 1), 0);
			}
		}
	}

	for (int x = 0; x < 8; x++)
	{
		//pawns
		pieces.push_back(new ChessPiece(ChessPieceType::pawn, _players[1]));
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

bool Table::SelectActivePiece(sf::Vector2i piecePosition)
{
	lastActivePiece = activePiece;
	for each (ChessPiece* piece in pieces)
	{
		if (piece->tablePosition.x == piecePosition.x && piece->tablePosition.y == piecePosition.y)
		{
			activePiece = piece;
			return true;
		}
	}

	return false;
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

void Table::SetSquareToMove(sf::Vector2i _position)
{
	squareToMove = board[_position.x][_position.y];
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

void Table::CheckMovement(const bool _whitePlayer, const sf::Vector2f _mousePosition)
{
	if (activePiece)
	{
		if ((activePiece->player.color == COLOR::WHITE && _whitePlayer) || (activePiece->player.color == COLOR::BLACK && !_whitePlayer))
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

bool Table::CheckForCheck(const bool _bottomPlayer, Square* _squareToMove)
{
	bool tempCheck = false;
	if (_bottomPlayer)
	{
		tempCheck = check[0];
	}
	else
	{
		tempCheck = check[1];
	}

	//This is created so we can restore the ActivePiece's current square easily
	Square* tempSquareActivePiece = nullptr;
	
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (board[x][y]->onSquare == activePiece)
			{
				tempSquareActivePiece = new Square(board[x][y]->isWhite, board[x][y]->tablePosition.x, board[x][y]->tablePosition.y);
				tempSquareActivePiece->onSquare = board[x][y]->onSquare;
				break;
			}
		}
	}
	
	//This is created for the square were we might eat a piece during the check
	Square* tempSquareEatenPiece = nullptr;

	if (_squareToMove->onSquare != nullptr)
	{
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if (board[x][y]->onSquare == activePiece)
				{
					tempSquareEatenPiece = new Square(board[x][y]->isWhite, board[x][y]->tablePosition.x, board[x][y]->tablePosition.y);
					tempSquareEatenPiece->onSquare = board[x][y]->onSquare;
					break;
				}
			}
		}
	}
	else
	{
		delete tempSquareEatenPiece;
	}
		
	//We use these tempPieces to revert the pieces to their original states
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
		//tempPieceEaten->GetSprite().setPosition(_squareToMove->onSquare->GetSprite().getPosition().x, _squareToMove->onSquare->GetSprite().getPosition().y);
	}

	//tempPieceActive = new ChessPiece(activePiece->type, activePiece->player);
	//tempPieceActive->allMoves = activePiece->allMoves;
	//tempPieceActive->checkingMoves = activePiece->checkingMoves;
	//tempPieceActive->isChecking = activePiece->isChecking;
	//tempPieceActive->lastPosition = activePiece->lastPosition;
	//tempPieceActive->possibleMoves = activePiece->possibleMoves;
	//tempPieceActive->tablePosition = activePiece->tablePosition;
	//tempPieceActive->GetSprite().setPosition(activePiece->GetSprite().getPosition().x, activePiece->GetSprite().getPosition().y);

	//first we need to make sure that by moving the active player doesn't allow his king to get checked
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
					break;
				}
			}
		}

		//remove the piece that was on _squareToMove
		EatPiece(_squareToMove->onSquare);
		_squareToMove->onSquare = nullptr;

		//next move the activePiece
		_squareToMove->onSquare = activePiece;
		activePiece->tablePosition = _squareToMove->tablePosition;
		
		//update the check situation		
		CalculatePieceMovementForEachPiece();		

		//check whether the active player is checked now
		UpdateCheckBoolStatus();

		//revert all movement
		bool found = false;

		//first we set the current tempPiece's position as the position of the original piece
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
					tempPieceEaten->GetSprite().setPosition(board[x][y]->sprite.getPosition().x, board[x][y]->sprite.getPosition().y);
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

		//we need to push this piece into the pieces since we deleted the original one
		pieces.push_back(tempPieceEaten);

		//if the active player is being checked, don't allow the move
		if ((_bottomPlayer && check[0]) || !_bottomPlayer && check[1])
		{
			return true;
		}
		//otherwise allow the move
		else
		{
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
		CalculatePieceMovementForEachPiece();

		//check whether the active player is checked now
		UpdateCheckBoolStatus();

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
		if ((_bottomPlayer && check[0]) || !_bottomPlayer && check[1])
		{
			//calculate the moves once more so that the game doesn't show wrong possible moves
			std::vector<ChessPiece*>::iterator piece = pieces.begin();

			for (; piece != pieces.end(); piece++)
			{
				CalculatePieceMovement((*piece));
			}

			//revert the check back to not being in check
			if (_bottomPlayer)
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
			if (_bottomPlayer)
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

bool Table::MoveOpponent(const bool _whitePlayerTurn, std::pair<sf::Vector2i, sf::Vector2i> moveData)
{
	SelectActivePiece(moveData.first);
		
	//Square* squareToMove = nullptr;

	//squareToMove = board[moveData.second.x][moveData.second.y];

	SetSquareToMove(moveData.second);

	if (!CheckForCheck(_whitePlayerTurn, squareToMove))
	{
		if (squareToMove->onSquare != nullptr)
		{
			EatPiece(squareToMove->onSquare);
		}

		//update where active piece has moved so far
		activePiece->allMoves.push_back(std::make_pair(activePiece->tablePosition, squareToMove->tablePosition));

		allMoves.push_back(std::make_pair(activePiece->tablePosition, squareToMove->tablePosition));

		//update en passant position
		if (activePiece->type == ChessPieceType::pawn)
		{
			//if player uses En passant maneuver, eat the pawn which left it's back unguarded
			if (squareToMove->tablePosition.x == enPassantPosition[0] && squareToMove->tablePosition.y == enPassantPosition[1])
			{
				if (activePiece->player.position == POSITION::DOWN)
				{
					if (board[squareToMove->tablePosition.x][squareToMove->tablePosition.y + 1]->onSquare != nullptr)
					{
						EatPiece(board[squareToMove->tablePosition.x][squareToMove->tablePosition.y + 1]->onSquare);
						board[squareToMove->tablePosition.x][squareToMove->tablePosition.y + 1]->onSquare = nullptr;
						enPassantPosition[0] = -12;
						enPassantPosition[1] = -12;
						enPassantPosition[2] = -12;
					}
				}
				else if (activePiece->player.position == POSITION::UP)
				{
					if (board[squareToMove->tablePosition.x][squareToMove->tablePosition.y - 1])
					{
						EatPiece(board[squareToMove->tablePosition.x][squareToMove->tablePosition.y - 1]->onSquare);
						board[squareToMove->tablePosition.x][squareToMove->tablePosition.y - 1]->onSquare = nullptr;
						enPassantPosition[0] = -12;
						enPassantPosition[1] = -12;
						enPassantPosition[2] = -12;
					}
				}
			}

			//update En passant position
			if (activePiece->tablePosition.y - squareToMove->tablePosition.y == 2)
			{
				enPassantPosition[0] = squareToMove->tablePosition.x;
				enPassantPosition[1] = squareToMove->tablePosition.y + 1;
				enPassantPosition[2] = 1;
			}
			else if (activePiece->tablePosition.y - squareToMove->tablePosition.y == -2)
			{
				enPassantPosition[0] = squareToMove->tablePosition.x;
				enPassantPosition[1] = squareToMove->tablePosition.y - 1;
				enPassantPosition[2] = 2;
			}
			else
			{
				if ((enPassantPosition[0] >= 0 && enPassantPosition[0] < 8) && (enPassantPosition[1] >= 0 && enPassantPosition[1] < 8))
				{
					enPassantPosition[0] = -12;
					enPassantPosition[1] = -12;
					enPassantPosition[2] = -12;
				}
			}
		}

		//check if the pawn gets to promote itself to a queen
		if (activePiece->type == ChessPieceType::pawn && (squareToMove->tablePosition.y == 0 || squareToMove->tablePosition.y == 7))
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
			enPassantPosition[2] = -12;
		}

		SetOnTable(activePiece, squareToMove);
		ClearActivePiece();

		//move successful
		//delete squareToMove;
		return true;
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
			sf::Vector2i startingPosition = sf::Vector2i(activePiece->tablePosition.x, activePiece->tablePosition.y);
			sf::Vector2i endingPosition = sf::Vector2i(_squareToMove->tablePosition.x, _squareToMove->tablePosition.y);

			activePiece->allMoves.push_back(std::make_pair(startingPosition, endingPosition));
			allMoves.push_back(std::make_pair(startingPosition, endingPosition));//.push_back(pair);

			//update en passant position
			if (activePiece->type == ChessPieceType::pawn)
			{
				//if player uses En passant maneuver, eat the pawn which left it's back unguarded
				if (_squareToMove->tablePosition.x == enPassantPosition[0] && _squareToMove->tablePosition.y == enPassantPosition[1])
				{
					if (activePiece->player.position == POSITION::DOWN)
					{
						if (board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y + 1]->onSquare != nullptr)
						{
							EatPiece(board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y + 1]->onSquare);
							board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y + 1]->onSquare = nullptr;
							enPassantPosition[0] = -12;
							enPassantPosition[1] = -12;
							enPassantPosition[2] = -12;
						}
					}
					else if (activePiece->player.position == POSITION::UP)
					{
						if (board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y - 1])
						{
							EatPiece(board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y - 1]->onSquare);
							board[_squareToMove->tablePosition.x][_squareToMove->tablePosition.y - 1]->onSquare = nullptr;
							enPassantPosition[0] = -12;
							enPassantPosition[1] = -12;
							enPassantPosition[2] = -12;
						}
					}
				}

				//update En passant position
				if (activePiece->tablePosition.y - _squareToMove->tablePosition.y == 2)
				{
					enPassantPosition[0] = _squareToMove->tablePosition.x;
					enPassantPosition[1] = _squareToMove->tablePosition.y + 1;
					enPassantPosition[2] = 1;
				}
				else if (activePiece->tablePosition.y - _squareToMove->tablePosition.y == -2)
				{
					enPassantPosition[0] = _squareToMove->tablePosition.x;
					enPassantPosition[1] = _squareToMove->tablePosition.y - 1;
					enPassantPosition[2] = 2;
				}
				else
				{
					if ((enPassantPosition[0] >= 0 && enPassantPosition[0] < 8) && (enPassantPosition[1] >= 0 && enPassantPosition[1] < 8))
					{
						enPassantPosition[0] = -12;
						enPassantPosition[1] = -12;
						enPassantPosition[2] = -12;
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
				enPassantPosition[2] = -12;
			}

			SetOnTable(activePiece, _squareToMove);		
			ClearActivePiece();

			//move successful
			return true;
		}
		else
		{
			CalculatePieceMovementForEachPiece();
			Deselect();
			return false;
		}
	}
	else
	{
		CalculatePieceMovementForEachPiece();
		Deselect();
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

	bool pieceIsChecking = false;

	switch (piece->type)
	{
	case ChessPieceType::pawn:
	{
		if (piece->player.position == POSITION::DOWN)
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
					if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 1]->onSquare->player.color != piece->player.color)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 1));

						if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 1]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}
					}
				}
			}

			//Eat right
			if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y - 1 > -1)
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare != nullptr)
				{
					if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare->player.color != piece->player.color)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 1));

						if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}
					}
				}
			}

			//Check En passant maneuver left
			if (enPassantPosition[0] > -1 && enPassantPosition[1] > -1)
			{
				if (enPassantPosition[0] == piece->tablePosition.x - 1 && piece->tablePosition.y - 1 == enPassantPosition[1] && enPassantPosition[2] == 2 )
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 1));
				}
			}

			//Check En passant maneuver right
			if (enPassantPosition[0] > +1 && enPassantPosition[1] > -1)
			{
				if (enPassantPosition[0] == piece->tablePosition.x + 1 && piece->tablePosition.y - 1 == enPassantPosition[1] && enPassantPosition[2] == 2)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 1));
				}
			}

		}
		else if (piece->player.position == POSITION::UP)
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
					}
				}
			}

			//Eat left
			if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y + 1 < 8)
			{
				if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare != nullptr)
				{
					if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare->player.color != piece->player.color)
					{
						if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 1));						
					}
				}
			}

			//Eat right
			if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y + 1 < 8)
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare != nullptr)
				{
					if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare->player.color != piece->player.color)
					{
						if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 1));						
					}
				}
			}

			//Check En passant maneuver left
			if (enPassantPosition[0] > -1 && enPassantPosition[1] > +1)
			{
				if (enPassantPosition[0] == piece->tablePosition.x - 1 && piece->tablePosition.y + 1 == enPassantPosition[1] && enPassantPosition[2] == 1)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 1));
				}
			}

			//Check En passant maneuver right
			if (enPassantPosition[0] > +1 && enPassantPosition[1] > +1)
			{
				if (enPassantPosition[0] == piece->tablePosition.x + 1 && piece->tablePosition.y + 1 == enPassantPosition[1] && enPassantPosition[2] == 1)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 1));
				}
			}
		}

		if (pieceIsChecking)
		{
			piece->player.color == COLOR::WHITE ? check[1] = true : check[0] = true;
			piece->isChecking = true;			
		}
		else
		{
			piece->isChecking = false;
		}
		break;
	}
	case ChessPieceType::knight:
	{

		if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y - 2 > -1)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 2]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 2));

			else if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 2]->onSquare->player.color != piece->player.color)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 2));

				if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 2]->onSquare->type == ChessPieceType::king)
				{
					pieceIsChecking = true;
				}
			}
		}

		if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y - 2 > -1)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 2]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 2));

			else if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 2]->onSquare->player.color != piece->player.color)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 2));

				if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 2]->onSquare->type == ChessPieceType::king)
				{
					pieceIsChecking = true;
				}
			}
		}

		if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y + 2 < 8)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 2]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 2));

			else if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 2]->onSquare->player.color != piece->player.color)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 2));

				if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 2]->onSquare->type == ChessPieceType::king)
				{
					pieceIsChecking = true;
				}
			}
		}

		if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y + 2 < 8)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 2]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 2));

			else if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 2]->onSquare->player.color != piece->player.color)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 2));

				if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 2]->onSquare->type == ChessPieceType::king)
				{
					pieceIsChecking = true;
				}
			}
		}

		if (piece->tablePosition.x + 2 < 8 && piece->tablePosition.y - 1 > -1)
		{
			if (board[piece->tablePosition.x + 2][piece->tablePosition.y - 1]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 2, piece->tablePosition.y - 1));

			else if (board[piece->tablePosition.x + 2][piece->tablePosition.y - 1]->onSquare->player.color != piece->player.color)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 2, piece->tablePosition.y - 1));

				if (board[piece->tablePosition.x + 2][piece->tablePosition.y - 1]->onSquare->type == ChessPieceType::king)
				{
					pieceIsChecking = true;
				}
			}
		}

		if (piece->tablePosition.x + 2 < 8 && piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x + 2][piece->tablePosition.y + 1]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 2, piece->tablePosition.y + 1));

			else if (board[piece->tablePosition.x + 2][piece->tablePosition.y + 1]->onSquare->player.color != piece->player.color)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 2, piece->tablePosition.y + 1));

				if (board[piece->tablePosition.x + 2][piece->tablePosition.y + 1]->onSquare->type == ChessPieceType::king)
				{
					pieceIsChecking = true;
				}
			}
		}

		if (piece->tablePosition.x - 2 > -1 && piece->tablePosition.y - 1 > -1)
		{
			if (board[piece->tablePosition.x - 2][piece->tablePosition.y - 1]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 2, piece->tablePosition.y - 1));

			else if (board[piece->tablePosition.x - 2][piece->tablePosition.y - 1]->onSquare->player.color != piece->player.color)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 2, piece->tablePosition.y - 1));

				if (board[piece->tablePosition.x - 2][piece->tablePosition.y - 1]->onSquare->type == ChessPieceType::king)
				{
					pieceIsChecking = true;
				}
			}
		}

		if (piece->tablePosition.x - 2 > -1 && piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x - 2][piece->tablePosition.y + 1]->onSquare == nullptr)
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 2, piece->tablePosition.y + 1));

			else if (board[piece->tablePosition.x - 2][piece->tablePosition.y + 1]->onSquare->player.color != piece->player.color)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 2, piece->tablePosition.y + 1));

				if (board[piece->tablePosition.x - 2][piece->tablePosition.y + 1]->onSquare->type == ChessPieceType::king)
				{
					pieceIsChecking = true;
				}
			}
		}

		if (pieceIsChecking)
		{	
			//piece->player.color == COLOR::WHITE ? check[1] = true : check[0] = true;
			piece->player.color == COLOR::WHITE ? check[1] = true : check[0] = true;
			
			piece->isChecking = true;			
		}
		else
		{
			piece->isChecking = false;
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
			}
			else
			{
				if (board[piece->tablePosition.x][i]->onSquare->player.color != piece->player.color)
				{
					if (board[piece->tablePosition.x][i]->onSquare->type == ChessPieceType::king)
					{
						pieceIsChecking = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
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
			}
			else
			{
				if (board[piece->tablePosition.x][i]->onSquare->player.color != piece->player.color)
				{
					if (board[piece->tablePosition.x][i]->onSquare->type == ChessPieceType::king)
					{
						pieceIsChecking = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
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
			}
			else
			{
				if (board[i][piece->tablePosition.y]->onSquare->player.color != piece->player.color)
				{
					if (board[i][piece->tablePosition.y]->onSquare->type == ChessPieceType::king)
					{
						pieceIsChecking = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
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
			}
			else
			{
				if (board[i][piece->tablePosition.y]->onSquare->player.color != piece->player.color)
				{
					if (board[i][piece->tablePosition.y]->onSquare->type == ChessPieceType::king)
					{
						pieceIsChecking = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
				}
				break;
			}
		}

		if (pieceIsChecking)
		{
			piece->player.color == COLOR::WHITE ? check[1] = true : check[0] = true;
			piece->isChecking = true;
		}
		else
		{
			piece->isChecking = false;
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
				}
				else
				{
					if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->player.color != piece->player.color)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y + y));

						if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}
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
				}
				else
				{
					if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->player.color != piece->player.color)
					{
						if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y + y));
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
				}
				else
				{
					if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->player.color != piece->player.color)
					{
						if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y - y));
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
				}
				else
				{
					if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->player.color != piece->player.color)
					{
						if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y - y));
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
		
		
		if (pieceIsChecking)
		{
			piece->player.color == COLOR::WHITE ? check[1] = true : check[0] = true;
			piece->isChecking = true;
		}
		else
		{
			piece->isChecking = false;
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
			}
			else
			{
				if (board[piece->tablePosition.x][i]->onSquare->player.color != piece->player.color)
				{
					if (board[piece->tablePosition.x][i]->onSquare->type == ChessPieceType::king)
					{
						pieceIsChecking = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
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
			}
			else
			{
				if (board[piece->tablePosition.x][i]->onSquare->player.color != piece->player.color)
				{
					if (board[piece->tablePosition.x][i]->onSquare->type == ChessPieceType::king)
					{
						pieceIsChecking = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, i));
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
			}
			else
			{
				if (board[i][piece->tablePosition.y]->onSquare->player.color != piece->player.color)
				{
					if (board[i][piece->tablePosition.y]->onSquare->type == ChessPieceType::king)
					{
						pieceIsChecking = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
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
			}
			else
			{
				if (board[i][piece->tablePosition.y]->onSquare->player.color != piece->player.color)
				{
					if (board[i][piece->tablePosition.y]->onSquare->type == ChessPieceType::king)
					{
						pieceIsChecking = true;
					}

					piece->possibleMoves.push_back(sf::Vector2i(i, piece->tablePosition.y));
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
				}
				else
				{
					if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->player.color != piece->player.color)
					{
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y + y));

						if (board[piece->tablePosition.x + x][piece->tablePosition.y + y]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}
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
				}
				else
				{
					if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->player.color != piece->player.color)
					{
						if (board[piece->tablePosition.x - x][piece->tablePosition.y + y]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}

						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y + y));
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
				}
				else
				{
					if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->player.color != piece->player.color)
					{
						if (board[piece->tablePosition.x + x][piece->tablePosition.y - y]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + x, piece->tablePosition.y - y));
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
				}
				else
				{
					if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->player.color != piece->player.color)
					{
						if (board[piece->tablePosition.x - x][piece->tablePosition.y - y]->onSquare->type == ChessPieceType::king)
						{
							pieceIsChecking = true;
						}
						piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - x, piece->tablePosition.y - y));
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

		if (pieceIsChecking)
		{
			piece->player.color == COLOR::WHITE ? check[1] = true : check[0] = true;
			piece->isChecking = true;
		}
		else
		{
			piece->isChecking = false;
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
			}
			else
			{
				if (board[piece->tablePosition.x][piece->tablePosition.y - 1]->onSquare->player.color != piece->player.color)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y - 1));
				}
			}
		}

		//bottom
		if (piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x][piece->tablePosition.y + 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y + 1));
			}
			else
			{
				if (board[piece->tablePosition.x][piece->tablePosition.y + 1]->onSquare->player.color != piece->player.color)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x, piece->tablePosition.y + 1));
				}
			}
		}

		//left
		if (piece->tablePosition.x - 1 > -1)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y));
			}
			else
			{
				if (board[piece->tablePosition.x - 1][piece->tablePosition.y]->onSquare->player.color != piece->player.color)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y));
				}
			}
		}

		//right
		if (piece->tablePosition.x + 1 < 8)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y));
			}
			else
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y]->onSquare->player.color != piece->player.color)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y));
				}
			}
		}

		//upper left
		if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y - 1 > -1)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 1));
			}
			else
			{
				if (board[piece->tablePosition.x - 1][piece->tablePosition.y - 1]->onSquare->player.color != piece->player.color)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y - 1));
				}
			}
		}

		//upper right
		if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y - 1 > -1)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 1));
			}
			else
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y - 1]->onSquare->player.color != piece->player.color)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y - 1));
				}
			}
		}

		//lower right
		if (piece->tablePosition.x + 1 < 8 && piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 1));
			}
			else
			{
				if (board[piece->tablePosition.x + 1][piece->tablePosition.y + 1]->onSquare->player.color != piece->player.color)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x + 1, piece->tablePosition.y + 1));
				}
			}
		}

		//lower left
		if (piece->tablePosition.x - 1 > -1 && piece->tablePosition.y + 1 < 8)
		{
			if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare == nullptr)
			{
				piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 1));
			}
			else
			{
				if (board[piece->tablePosition.x - 1][piece->tablePosition.y + 1]->onSquare->player.color != piece->player.color)
				{
					piece->possibleMoves.push_back(sf::Vector2i(piece->tablePosition.x - 1, piece->tablePosition.y + 1));
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

void Table::UpdateCheckBoolStatus()
{
	bool tempCheck[2] {false, false};

	for each (ChessPiece* piece in pieces)
	{
		if (piece->player.color == COLOR::WHITE && piece->isChecking)
		{
			tempCheck[1] = true;
		}
		else if (piece->player.color == COLOR::BLACK && piece->isChecking)
		{
			tempCheck[0] = true;
		}
	}

	check[0] = tempCheck[0];
	check[1] = tempCheck[1];
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

bool Table::Checkmate(const bool _playerOneTurn)
{
	for each (ChessPiece* piece in pieces)
	{
		if (piece->player.position == POSITION::DOWN && check[0])
		{
			if (!piece->possibleMoves.empty())
			{
				std::vector<sf::Vector2i>::reverse_iterator move = piece->possibleMoves.rbegin();
				for (; move != piece->possibleMoves.rend(); move++)
				{					
					if (!CheckForCheck(_playerOneTurn, board[move->x][move->y]))
					{
						//piece->possibleMoves.erase(move);

					}
				}
			}
		}
		else if (piece->player.position == POSITION::UP && check[1])
		{

		}
	}

	return true;
}

void Table::DebugStuff()
{
	/*system("cls");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[j][i]->onSquare != nullptr)
			{
				switch (board[j][i]->onSquare->type)
				{
				case pawn:
					if (board[j][i]->onSquare->player.position == POSITION::DOWN)
						printf("P");
					else
						printf("p");
					break;
				case knight:
					if (board[j][i]->onSquare->player.position == POSITION::DOWN)
						printf("N");
					else
						printf("n");
					break;
				case rook:
					if (board[j][i]->onSquare->player.position == POSITION::DOWN)
						printf("R");
					else
						printf("r");
					break;
				case bishop:
					if (board[j][i]->onSquare->player.position == POSITION::DOWN)
						printf("B");
					else
						printf("b");
					break;
				case queen:
					if (board[j][i]->onSquare->player.position == POSITION::DOWN)
						printf("Q");
					else
						printf("q");
					break;
				case king:
					if (board[j][i]->onSquare->player.position == POSITION::DOWN)
						printf("K");
					else
						printf("k");
					break;
				default:
					printf("X");
					break;
				}
				
			}
			else if (board[j][i]->onSquare == nullptr)
			{
				printf(".");
			}
		}
		printf("\n");
	}

	if (activePiece)
		printf("\n ActivePiece Position \n x: %d  y: %d \n", activePiece->tablePosition.x, activePiece->tablePosition.x);
	else
		printf("\n No ActivePiece \n");

	printf("\nEn passant position \n");
	printf("x: %d\n y: %d\n", enPassantPosition[0], enPassantPosition[1]);

	printf("\nCheck Status:\n");
	printf("player 1: %d\nplayer 2: %d", check[0], check[1]);
	*/
}