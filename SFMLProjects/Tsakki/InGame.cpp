#include "InGame.h"



void InGame::Initialize()
{
	board.Initialize();
	playerOneTurn = true;
}

void InGame::Loop(sf::RenderWindow* _window, const sf::Vector2f _mousePosition)
{
	//logic
	HandleTurn(_window, _mousePosition);

	//draw
	_window->clear();

	//Here we draw all the pieces,
	//squares and highlights
	this->Draw(_window);

	_window->display();
}

bool InGame::HandleTurn(sf::RenderWindow* _window, const sf::Vector2f _mousePosition)
{
	board.SelectActivePiece(_mousePosition);

	if (playerOneTurn)
	{
		if (Move(1, _window, _mousePosition))
		{
			EndTurn();
		}
	}
	else
	{
		if (Move(2, _window, _mousePosition))
		{
			EndTurn();
		}
	}

	return false;
}

bool InGame::Move(const int _player, sf::RenderWindow* _window, const sf::Vector2f _mousePosition)
{
	if (board.GetActivePiece()->player == _player)
	{
		//board.GetLegalPositions();
		return true;

	}

	return false;
}

void InGame::Draw(sf::RenderWindow* _window)
{
	_window->clear(sf::Color(0, 0, 150, 255));

	board.Draw(_window);
}

void InGame::EndTurn()
{
	board.ClearHighlights();
}

void InGame::Uninitialize()
{
	board.Uninitialize();
}

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
