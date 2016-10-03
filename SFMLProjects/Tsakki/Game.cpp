#include "Game.h"

#include <iostream>


Game::Game()
{
	screenResolution = new sf::Vector2u(800, 600);	
	
	window = new sf::RenderWindow(sf::VideoMode(screenResolution->x, screenResolution->y), "Tsakki");
	window->setKeyRepeatEnabled(false);
}

Game::~Game()
{
	delete screenResolution;
	delete window;
}

void Game::Initialize()
{
	stateManager.Initialize();
}

void Game::Uninitialize()
{
	stateManager.Uninitialize();
}

void Game::Loop()
{
	//state ei välttämättä vaihu
	while (stateManager.GetState() != nullptr)
	{
		//calculate mouse position
		mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		HandleInput();	

		//for debugging
		system("cls");
		printf("x: %f \ny: %f \n", mousePosition.x, mousePosition.y);

		//run state main loop
		stateManager.GetState()->Loop(window, mousePosition);
	}
}

void Game::HandleInput()
{
	sf::Event event;

	while (window->pollEvent(event))
	{	
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else
		{
			stateManager.GetState()->HandleInput(event.type);
		}
	}
}

//
//void Game::Initialize()
//{
//	table.Initialize();	
//
//	turnOrder.push(1);
//}

//void Game::Loop()
//{
//	while (window->isOpen())
//	{
//
//		table.ShowAccessibleSquares();
//
//		window->clear();
//		this->Draw();
//		window->display();
//	}
//}
//
//void Game::Uninitialize()
//{
//	table.Uninitialize();
//}

//void Game::Draw()
//{	
//	window->clear(sf::Color(0, 0, 150, 255));
//
//	table.Draw(window);
//}
//
//void Game::HandleTurn()
//{
//	//Check whose turn it is
//	int playerNum = turnOrder.front();
//
//	turnOrder.pop();
//	
//	//add a new turn to the queue
//	if (playerNum == 2)
//	{
//		turnOrder.push(1);
//	}
//	else
//	{
//		turnOrder.push(2);
//	}
//
//	//handle the actual turn
//	switch (playerNum)
//	{
//	case 1:
//	{
//		//check if player has moved
//		//if yes, end turn
//		if (Move())
//		{
//			EndTurn();
//		}
//		break;
//	}
//	case 2:
//	{
//		if (Move())
//		{
//			EndTurn();
//		}
//		break;
//	}
//	default:
//		break;
//	}
//}

//void Game::EndTurn()
//{
//	table.ClearHighlights();
//}

//bool Game::Move()
//{
//	bool movementDone = false;
//
//	sf::Event event;
//	while (window->pollEvent(event))
//	{
//		if (event.type == sf::Event::Closed)
//			window->close();
//
//		movementDone = HandleInput();
//	}
//
//	return movementDone;
//}

//bool Game::HandleInput()
//{
//	//mouse position
//	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
//	system("cls");
//	std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
//
//	 return table.HandleInput(mousePosition);
//}