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

			if ((whitePlayerTurn && players[0].color == COLOR::WHITE) || (!whitePlayerTurn && players[0].color == COLOR::BLACK))
			{
				if (Move())
				{
					EndTurn();
					return true;
				}
			}
			else if ((whitePlayerTurn && players[1].color == COLOR::WHITE) || (!whitePlayerTurn && players[1].color == COLOR::BLACK))
			{
				if (WaitForMoveFromOpponent())
				{
					EndTurn();
					return true;
				}
			}
			else
			{
				return false;
			}
			break;
		}
		case GAMETYPE::JOIN:
		{
			board.SetSquaresForHighlighting();

			if ((whitePlayerTurn && players[0].color == COLOR::WHITE) || (!whitePlayerTurn && players[0].color == COLOR::BLACK))
			{
				if (Move())
				{
					EndTurn();
					return true;
				}
			}
			else if ((whitePlayerTurn && players[1].color == COLOR::WHITE) || (!whitePlayerTurn && players[1].color == COLOR::BLACK))
			{
				if (WaitForMoveFromOpponent())
				{
					EndTurn();
					return true;
				}
			}
			else
			{
				return false;
			}
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

bool InGame::WaitForMoveFromOpponent()
{
	PacketData* data = nullptr;
	bool moveReceived = false;

	data = network->ListenForPackets();

	if (data != nullptr)
	{
		if (data->packetType == PACKETTYPE::MOVE)
		{
			std::pair<sf::Vector2i, sf::Vector2i> move;
			sf::Int32 moveInt = data->moveData;
			move = ConvertIntIntoPair(moveInt);
			return board.MoveOpponent(whitePlayerTurn, move);
		}

		return false;
	}
	else
	{
		return false;
	}
}

bool InGame::Move()
{
	switch (gameType)
	{
	case GAMETYPE::JOIN:
	case GAMETYPE::HOST:
	{
		if (board.GetSquareToMove())
		{
			if (board.MoveActivePiece(whitePlayerTurn, board.GetSquareToMove()))
			{
				network->SendMove(ConvertToString(board.GetAllMoves().back()));
				return true;
			}
		}
		else
		{
			return false;
		}
		break;
	}	
	case GAMETYPE::HOTSEAT:
	{
		if (board.GetSquareToMove())
		{
			
			return board.MoveActivePiece(whitePlayerTurn, board.GetSquareToMove());
		}
		else
		{
			return false;
		}
		break;
	}
	case GAMETYPE::AGAINSTAI:
		break;
	default:
		break;
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










std::string InGame::ConvertToString(std::pair<sf::Vector2i, sf::Vector2i> _pair)
{
	int coordinations[4] = { 0 };
	coordinations[0] = _pair.first.x;
	coordinations[1] = _pair.first.y;
	coordinations[2] = _pair.second.x;
	coordinations[3] = _pair.second.y;

	std::string move = "";

	for (size_t i = 0; i < 4; i++)
	{
		switch (coordinations[i])
		{
		case 0:
		{
			if (i % 2 == 0)
			{
				move += 'A';
			}
			else
			{
				move += '1';
			}
			break;
		}
		case 1:
		{
			if (i % 2 == 0)
			{
				move += 'B';
			}
			else
			{
				move += '2';
			}
			break;
		}
		case 2:
		{
			if (i % 2 == 0)
			{
				move += 'C';
			}
			else
			{
				move += '3';
			}
			break;
		}
		case 3:
		{
			if (i % 2 == 0)
			{
				move += 'D';
			}
			else
			{
				move += '4';
			}
			break;
		}
		case 4:
		{
			if (i % 2 == 0)
			{
				move += 'E';
			}
			else
			{
				move += '5';
			}
			break;
		}
		case 5:
		{
			if (i % 2 == 0)
			{
				move += 'F';
			}
			else
			{
				move += '6';
			}
			break;
		}
		case 6:
		{
			if (i % 2 == 0)
			{
				move += 'G';
			}
			else
			{
				move += '7';
			}
			break;
		}
		case 7:
		{
			if (i % 2 == 0)
			{
				move += 'H';
			}
			else
			{
				move += '8';
			}
			break;
		}
		default:
			break;
		}
	}

	return move;
}

std::pair<sf::Vector2i, sf::Vector2i> InGame::ConvertToVec(std::string _move)
{
	int startX, startY, endX, endY;

	for (size_t i = 0; i < 4; i++)
	{

		if (_move.at(i) == 'A')
		{
			if (i < 2)
			{
				startX = 0;
			}
			else
			{
				endX = 0;
			}
			break;
		}
		else if (_move.at(i) == 'B')
		{
			if (i < 2)
			{
				startX = 1;
			}
			else
			{
				endX = 1;
			}
			break;
		}
		else if (_move.at(i) == 'C')
		{
			if (i < 2)
			{
				startX = 2;
			}
			else
			{
				endX = 2;
			}
			break;
		}
		else if (_move.at(i) == 'D')
		{
			if (i < 2)
			{
				startX = 3;
			}
			else
			{
				endX = 3;
			}
			break;
		}
		else if (_move.at(i) == 'E')
		{
			if (i < 2)
			{
				startX = 4;
			}
			else
			{
				endX = 4;
			}
			break;
		}
		else if (_move.at(i) == 'F')
		{
			if (i < 2)
			{
				startX = 5;
			}
			else
			{
				endX = 5;
			}
			break;
		}
		else if (_move.at(i) == 'G')
		{
			if (i < 2)
			{
				startX = 6;
			}
			else
			{
				endX = 6;
			}
			break;
		}
		else if (_move.at(i) == 'H')
		{
			if (i < 2)
			{
				startX = 7;
			}
			else
			{
				endX = 7;
			}
			break;
		}
		else if (_move.at(i) == '1')
		{
			if (i < 2)
			{
				startY = 0;
			}
			else
			{
				endY = 0;
			}
			break;
			break;
		}
		else if (_move.at(i) == '2')
		{
			if (i < 2)
			{
				startY = 1;
			}
			else
			{
				endY = 1;
			}
			break;
		}
		else if (_move.at(i) == '3')
		{
			if (i < 2)
			{
				startY = 2;
			}
			else
			{
				endY = 2;
			}
			break;
		}
		else if (_move.at(i) == '4')
		{
			if (i < 2)
			{
				startY = 3;
			}
			else
			{
				endY = 3;
			}
			break;
		}
		else if (_move.at(i) == '5')
		{
			if (i < 2)
			{
				startY = 4;
			}
			else
			{
				endY = 4;
			}
			break;
		}
		else if (_move.at(i) == '6')
		{
			if (i < 2)
			{
				startY = 5;
			}
			else
			{
				endY = 5;
			}
			break;
		}
		else if (_move.at(i) == '7')
		{
			if (i < 2)
			{
				startY = 6;
			}
			else
			{
				endY = 6;
			}
			break;
		}
		else if (_move.at(i) == '8')
		{
			if (i < 2)
			{
				startY = 7;
			}
			else
			{
				endY = 7;
			}
			break;
		}
	}

	return std::make_pair(sf::Vector2i(startX, startY), sf::Vector2i(endX, endY));
}

std::pair<sf::Vector2i, sf::Vector2i> InGame::ConvertIntIntoPair(sf::Int32 _toBeConverter)
{
	int converted = _toBeConverter;

	//converted = ~converted;

	int intMove[4] = { 0 };

	char tempMove[4];
	tempMove[0] = (converted >> 24);
	tempMove[1] = (converted >> 16);
	tempMove[2] = (converted >> 8);
	tempMove[3] = (converted >> 0);

	for (size_t i = 0; i < 4; i++)
	{
		switch (tempMove[i])
		{
			case '1':
			case 'A':
			{
				intMove[i] = 0;
				break;
			}
			case '2':
			case 'B':
			{
				intMove[i] = 1;
				break;
			}
			case '3':
			case 'C':
			{
				intMove[i] = 2;
				break;
			}
			case '4':
			case 'D':
			{
				intMove[i] = 3;
				break;
			}
			case '5':
			case 'E':
			{
				intMove[i] = 4;
				break;
			}
			case '6':
			case 'F':
			{
				intMove[i] = 5;
				break;
			}
			case '7':
			case 'G':
			{
				intMove[i] = 6;
				break;
			}
			case '8':
			case 'H':
			{
				intMove[i] = 7;
				break;
			}			
			default:
				break;
		}
	}

	/*std::string unpackedMove = "";
	unpackedMove.append(move);*/

	//sf::Vector2i startingPosition = sf::Vector2i(move[0], move[1]);
	//sf::Vector2i endPosition = sf::Vector2i(move[2], move[3]);



	return std::make_pair(sf::Vector2i(intMove[0], intMove[1]), sf::Vector2i(intMove[2], intMove[3]));
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
