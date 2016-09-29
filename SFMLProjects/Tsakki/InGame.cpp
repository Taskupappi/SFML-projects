#include "InGame.h"

void InGame::Initialize()
{
	board.Initialize();
	playerOneTurn = true;
}
void InGame::Loop(sf::RenderWindow* _window)
{

	board.ShowAccessibleSquares();
	
	_window->clear();
	this->Draw(_window);
	_window->display();

}
void InGame::Uninitialize()
{
	board.Uninitialize();
}
void InGame::Draw(sf::RenderWindow* _window)
{
	_window->clear(sf::Color(0, 0, 150, 255));
	
	board.Draw(_window);
}
void InGame::HandleInput()
{

}

void InGame::HandleTurn()
{


	if (playerOneTurn)
	{
		Move(1);
	}
	else
	{
		Move(2);
	}


}
void InGame::EndTurn()
{

}


bool InGame::Move(int _player)
{
	switch (_player)
	{
		case 1:
		{

		}
			break;
		case 2:
		{

		}
			break;

		default:
			break;
	}
	return false;
}
