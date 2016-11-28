#include "InGame.h"

InGame::InGame(GameStateManager* _stateManager, GAMETYPE _type)
{
	type = _type;
	 stateManager = _stateManager;
	 network = nullptr;
}

void InGame::Initialize()
{
	switch (type)
	{
		case HOST:
		{
			SetupHost(isHost);
			board.Initialize();
			playerOneTurn = true;
			break;
		}	
		case JOIN:
		{
			SetupHost(isHost);
			board.Initialize();
			
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

void InGame::SetupHost(const bool isHost)
{
	network = new Network(isHost);

	network->Initialize();

	if (isHost)
	{



		//
		//#include <iostream>
		//
		////network
		//char* Decrypt(__int32 toBeDecryptedMove);
		//__int32 PackMove(const char move[]);
		//
		////not a host
		//void AskForPacket(sf::UdpSocket socket);
		//
		////ui
		//sf::IpAddress hostIP = "172.31.16.55";
		//unsigned short port = 35795;
		//int host = -1;
		//bool quit = false;
		//
		//char textBuffer[100];
		//__int32 buffer;
		//std::size_t received;
		//
		//sf::TcpSocket tcpSocket;
		//
		//std::thread receiverThread;
		//std::thread senderThread;
		//std::thread mainThread;
		//
		//
		//
		//int main()
		//{
		//	
		//
		//
		//	hostIP = sf::IpAddress::getLocalAddress();
		//	std::string text = "connected to ";
		//	char connectionType, mode;
		//
		//	char testMove[4];
		//	testMove[0] = 'e';
		//	testMove[1] = '4';
		//	testMove[2] = 'e';
		//	testMove[3] = '5';
		//
		//	__int32 moveTestInt = PackMove(testMove);
		//
		//	std::cout << "Enter (s) for server or (c) for client" << std::endl;
		//	std::cin >> connectionType;
		//
		//	if (connectionType == 's')
		//	{
		//		sf::TcpListener listener;
		//		listener.listen(port);
		//		listener.accept(tcpSocket);
		//		text += "server";
		//		mode = 's';
		//	}
		//	else if (connectionType == 'c')
		//	{
		//		std::string tempIP = "";
		//		std::cout << "Give server address" << std::endl;
		//		std::cin >> tempIP;
		//		
		//		sf::Time time;
		//
		//		time.asSeconds();
		//
		//		tcpSocket.connect(tempIP, port);
		//		
		//
		//		text += "client";
		//		mode = 'r';
		//	}
		//	else
		//	{
		//		return 0;
		//	}
		//
		//	text = "rum8";
		//
		//	tcpSocket.send(text.c_str(), text.length() + 1);
		//
		//	tcpSocket.receive(&buffer, sizeof(buffer), received);
		//
		//	std::cout << buffer << std::endl;
		//
		//	bool done = false;
		//
		//	while (!done)
		//	{ 
		//		if (mode == 's') //send
		//		{
		//			std::getline(std::cin, text);
		//			__int32 move = PackMove(text.c_str());
		//			//std::cout << "move: " << &move << std::endl;
		//			tcpSocket.send(&move, sizeof(move));
		//			
		//			
		//			//tcpSocket.send(text.c_str(), text.length() + 1);
		//			mode = 'r';
		//		}
		//		else if (mode == 'r') //receive
		//		{
		//			tcpSocket.receive(&buffer, sizeof(buffer), received);
		//			//tcpSocket.receive(textBuffer, sizeof(textBuffer), received);			
		//			if (received > 0)
		//			{
		//				//std::cout << "Received: " << textBuffer << std::endl;
		//				std::cout << "Received: " << ~buffer << std::endl;
		//				mode = 's';
		//			}		
		//		}
		//	}
		//}
		//
		//char* Decrypt(__int32 toBeDecryptedMove)
		//{
		//	toBeDecryptedMove = ~toBeDecryptedMove;
		//
		//	char move[4];
		//	move[0] = (toBeDecryptedMove >> 24);
		//	move[1] = (toBeDecryptedMove >> 16);
		//	move[2] = (toBeDecryptedMove >> 8);
		//	move[3] = (toBeDecryptedMove >> 0);
		//
		//	return move;
		//}
		//
		//__int32 PackMove(const char move[])
		//{
		//	//turn char formatted move into an integer
		//	__int32 tempPacket = 0;
		//
		//	tempPacket = (move[0] << 24) + (move[1] << 16) + (move[2] << 8) + (move[3]);
		//
		//	tempPacket = ~tempPacket;
		//
		//	return tempPacket;
		//}

	}
	else
	{

	}
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
