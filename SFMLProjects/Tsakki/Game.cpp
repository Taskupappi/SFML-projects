#include "Game.h"

#include <iostream>


Game::Game()
{
	screenResolution = new sf::Vector2u(800, 600);	
	
	window = new sf::RenderWindow(sf::VideoMode(screenResolution->x, screenResolution->y), "Tsakki");
	window->setKeyRepeatEnabled(false);
	textManager = new TextManager();
}

Game::~Game()
{
	delete textManager;
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
	while (window->isOpen())
	{
		//calculate mouse position
		mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));		

		HandleInput();

		//run state main loop
		stateManager.GetStateFront()->Loop(window, mousePosition, textManager);
	}
}

void Game::HandleInput()
{
	sf::Event event;

	bool update = true;

	while (window->pollEvent(event))
	{	
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			update = true;
		}
		else if (event.type == sf::Event::LostFocus)
		{
			update = false;
		}
		else
		{
			if (update)
			{
				stateManager.GetStateFront()->HandleInput(event, mousePosition);
			}
		}
	}
}
