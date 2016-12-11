#include "InGame.h"
#include <iostream>

InGame::InGame(GameStateManager* _stateManager, GAMETYPE _type)
{
	gameType = _type;
	 stateManager = _stateManager;
	 network = nullptr;
	 whitePlayerTurn = true;
}

void InGame::DecideColor()
{
	unsigned short decision;
	std::cout << "Do you go as white or black?" << std::endl;
	std::cout << "1) white 2) black" << std::endl;
	std::cin >> decision;

	if (decision == 1)
	{
		players[0].color = COLOR::WHITE;
		players[1].color = COLOR::BLACK;
	}
	else if (decision == 2)
	{
		players[0].color = COLOR::BLACK;
		players[1].color = COLOR::WHITE;
	}
	else
	{
		std::cout << "not a valid decision! " << std::endl;
		DecideColor();
	}
}

void InGame::Initialize()
{
	switch (gameType)
	{
	case GAMETYPE::HOST:
		{
			players[0].position = POSITION::DOWN;
			players[1].position = POSITION::UP;
			
			//set player types
			players[0].type = PLAYERTYPE::LOCAL;
			players[1].type = PLAYERTYPE::INTERNET;

			//Let host decide it's color
			DecideColor();

			//setup network
			isHost = true;
			SetupHost(isHost);		

			if (players[0].color == COLOR::WHITE)
				network->SendHostColor(true);
			else
				network->SendHostColor(false);

			//set board ready
			board.Initialize(players);

			network->SetBlocking(false);
			break;
		}	
		case GAMETYPE::JOIN:
		{
			players[0].position = POSITION::DOWN;
			players[1].position = POSITION::UP;

			//setup network stuff ready
			SetupHost(isHost);

			PacketData* data = nullptr;
			bool colorReceived = false;

			while (!colorReceived)
			{
				//wait for host color
				data = network->ListenForPackets();

				if (data->message == "isWhite")
				{
					players[0].color = COLOR::BLACK;
					players[1].color = COLOR::WHITE;
					colorReceived = true;
				}
				else if (data->message == "notWhite")
				{
					players[0].color = COLOR::WHITE;
					players[1].color = COLOR::BLACK;
					colorReceived = true;
				}
			}

			//set player types
			players[0].type = PLAYERTYPE::LOCAL;
			players[1].type = PLAYERTYPE::INTERNET;

			//set board ready
			board.Initialize(players);		

			network->SetBlocking(false);
			break;
		}
		case GAMETYPE::HOTSEAT:
		{
			//no need to ask for colors since both are local players
			players[0].color = COLOR::WHITE;
			players[1].color = COLOR::BLACK;

			//set player types
			players[0].type = PLAYERTYPE::LOCAL;
			players[1].type = PLAYERTYPE::LOCAL;

			players[0].position = POSITION::DOWN;
			players[1].position = POSITION::UP;

			//set board ready
			board.Initialize(players);
			break;
		}
		case GAMETYPE::AGAINSTAI:
		{
			break;
		}
	default:
		break;
	}	
}

void InGame::SetupHost(const bool isHost)
{
	network = new Network(isHost);

	network->Initialize();
}

void InGame::BeginTurn(sf::RenderWindow* _window)
{
	switch (gameType)
	{
		case GAMETYPE::HOST:
		{
			//Do this only once per turn
			board.CalculatePieceMovementForEachPiece();
			
			beginTurnStep = false;
			break;
		}
		case GAMETYPE::JOIN:
		{
			//Do this only once per turn
			board.CalculatePieceMovementForEachPiece();			
			
			beginTurnStep = false;
			break;
		}
		case GAMETYPE::HOTSEAT:
		{
			//Do this only once per turn
			board.CalculatePieceMovementForEachPiece();

			board.UpdateCheckBoolStatus();

			beginTurnStep = false;
			break;
		}
		case GAMETYPE::AGAINSTAI:
		{
			break;
		}
	}



}

void InGame::SetPlayerTurnText(TextManager* _textManager)
{
	if (whitePlayerTurn)
	{
		_textManager->AddText(TEXTTYPE::PLAYERTURN,"White's Turn");
	}
	else
	{
		_textManager->AddText(TEXTTYPE::PLAYERTURN, "Black's Turn");
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
	switch (gameType)
	{
		case GAMETYPE::HOST:
		{
			board.SetSquaresForHighlighting();

			if (whitePlayerTurn && players[0].color == COLOR::WHITE)
			{
				if (Move())
				{
					EndTurn();
					return true;
				}
			}
			else if (!whitePlayerTurn && players[1].color == COLOR::BLACK)
			{
				if (Move())
				{
					EndTurn();
					return true;
				}
			}
			return false;
			break;
		}
		case GAMETYPE::JOIN:
		{
			board.SetSquaresForHighlighting();
			
			if (whitePlayerTurn && players[0].color == COLOR::WHITE)
			{
				if (Move())
				{
					EndTurn();
					return true;
				}
			}
			else if(!whitePlayerTurn && players[0].color == COLOR::BLACK)
			{
				if (Move())
				{
					EndTurn();
					return true;
				}
			}
			else
			{				
				return WaitForMoveFromServer();
			}
			return false;
			break;
		}
		case GAMETYPE::HOTSEAT:
		{
			board.SetSquaresForHighlighting();

			if (whitePlayerTurn)
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
			break;
		}
		case GAMETYPE::AGAINSTAI:
		{
			break;
		}
		default:
			break;
	}
	return false;
	
}

bool InGame::WaitForMoveFromServer()
{
	PacketData* data = nullptr;
	bool moveReceived = false;

	/*while (!moveReceived)
	{*/
		//wait for host color
	data = network->ListenForPackets();
	//}

	if (data != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool InGame::Move()
{
	//switch (gameType)
	//{
	//case GAMETYPE::HOST:
	//	break;
	//case GAMETYPE::JOIN:
	//	break;
	//case GAMETYPE::HOTSEAT:
	//	break;
	//case GAMETYPE::AGAINSTAI:
	//	break;
	//default:
	//	break;
	//}

	if (board.GetSquareToMove())
	{
		return board.MoveActivePiece(whitePlayerTurn, board.GetSquareToMove());	
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

	if (whitePlayerTurn)
	{
		whitePlayerTurn = false;
	}
	else
	{
		whitePlayerTurn = true;
	}

	beginTurnStep = true;
	board.ClearActivePiece();	
	//movementDone = false;
}

void InGame::Uninitialize()
{
	delete network;

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
					board.CheckMovement(whitePlayerTurn, _mousePosition);
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
//				if (event.gameType == sf::Event::Closed)
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
