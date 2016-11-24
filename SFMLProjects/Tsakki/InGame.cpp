#include "InGame.h"

InGame::InGame(GameStateManager* _stateManager, GAMETYPE _type)
{
	type = _type;
	 stateManager = _stateManager;
}

void InGame::Initialize()
{
	switch (type)
	{
		case HOST:
		{		
			SetupHost();
			board.Initialize();
			playerOneTurn = true;
			break;
		}	
		case JOIN:
		{
			break;
		}
	
		case HOTSEAT:
		{
			board.Initialize();
			playerOneTurn = true;
			break;
		}

		case AI:
		{
			break;
		}
	default:
		break;
	}

	
}

void InGame::SetupHost()
{

}

void InGame::BeginTurn(sf::RenderWindow* _window)
{
	//Do this only once per turn
	board.CalculatePieceMovementForEachPiece();

	board.UpdateCheckBoolStatus();

	beginTurnStep = false;
}

void InGame::SetPlayerTurnText(TextManager* _textManager)
{
	if (playerOneTurn)
	{
		_textManager->AddText(TEXTTYPE::PLAYERTURN,"Player 1 Turn");
	}
	else
	{
		_textManager->AddText(TEXTTYPE::PLAYERTURN, "Player 2 Turn");
	}
}

void InGame::Loop(sf::RenderWindow* _window, const sf::Vector2f _mousePosition, TextManager* _textManager)
{
	if (beginTurnStep)
	{
		BeginTurn(_window);
		SetPlayerTurnText(_textManager);
	}

	//logic
	HandleTurn(_window, _mousePosition);

	//draw
	_window->clear();

	//Here we draw all the pieces,
	//squares, highlights and text
	//
	this->Draw(_window, _textManager);

	_window->display();	
}

bool InGame::HandleTurn(sf::RenderWindow* _window, const sf::Vector2f _mousePosition)
{
	//board.SelectActivePiece(_mousePosition);
	
	board.SetSquaresForHighlighting();

	if (playerOneTurn)
	{		
		if (Move())
		{
			EndTurn();
			return true;
		}
	}
	else
	{
		if (Move())
		{
			EndTurn();
			return true;
		}
	}

	return false;
}

bool InGame::Move()
{
	if (board.GetSquareToMove())
	{
		return board.MoveActivePiece(playerOneTurn, board.GetSquareToMove());	
	}
	else
	{
		return false;
	}
}

void InGame::Draw(sf::RenderWindow* _window, TextManager* _textManager)
{
	_window->clear(sf::Color(0, 0, 150, 255));

	board.Draw(_window);
	
	_textManager->Draw(_window);
}

void InGame::EndTurn()
{
	board.CalculatePieceMovementForEachPiece();

	board.UpdateCheckBoolStatus();

	board.ClearActivePiece();
	board.ClearHighlights();

	if (playerOneTurn)
	{
		playerOneTurn = false;
	}
	else
	{
		playerOneTurn = true;
	}

	beginTurnStep = true;
	board.ClearActivePiece();	
	//movementDone = false;
}

void InGame::Uninitialize()
{
	board.Uninitialize();
}

void InGame::HandleInput(const sf::Event _inputEvent, const sf::Vector2f _mousePosition)
{
	mouseToBoardPosition = board.MousePositionToTablePosition(_mousePosition);

	switch (_inputEvent.type)
	{	
		case sf::Event::MouseButtonReleased:
		{			
			if (_inputEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (board.GetActivePiece())
				{
					board.CheckMovement(playerOneTurn, _mousePosition);
				}
				else
				{
					board.SelectActivePiece(_mousePosition);
				}
			}
			else if (_inputEvent.mouseButton.button == sf::Mouse::Right)
			{
				board.Deselect();
			}
			
			break;
		}
		default:
			break;
	}
}

/*
bool InGame::Move(const int _player, const sf::Vector2f _mousePosition)
{
	board.PrintMouseTablePosition();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (board.GetActivePiece())
		{
			//check if the active piece is controlled by the player whose turn it is
			if (board.GetActivePiece()->player == _player)
			{
				for each (Square* square in board.GetHighlightedSquares())
				{
					if (square->sprite.getGlobalBounds().contains(_mousePosition))
					{
						board.GetActivePiece()->GetSprite().setPosition(square->sprite.getPosition().x, square->sprite.getPosition().y);
						board.GetActivePiece()->tablePosition = square->tablePosition;
						board.GetActivePiece()->hasMoved = true;
						return true;
					}
				}
			}
		}
	}
	return false;
}
*/

//bool InGame::Move(int _player, sf::RenderWindow* _window, const sf::Vector2f _mousePosition)
//{
//	switch (_player)
//	{
//		case 1:
//		{
//			bool movementDone = false;
//			
//				
//			
//				return movementDone;*/
//		}
//			break;
//		case 2:
//		{
//			/*bool movementDone = false;
//
//			sf::Event event;
//			while (window->pollEvent(event))
//			{
//				if (event.type == sf::Event::Closed)
//					window->close();
//
//				movementDone = HandleInput();
//			}
//
//			return movementDone;*/
//		}
//			break;
//
//		default:
//			break;
//	}
//	return false;
//}
