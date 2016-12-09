#include "InGame.h"
#include "MainMenu.h"
#include <iostream>


MainMenu::MainMenu(GameStateManager* _stateManager)
{
	stateManager = _stateManager;
}

void MainMenu::Initialize()
{
}

void MainMenu::Loop(sf::RenderWindow* window, const sf::Vector2f mousePosition, TextManager* textManager)
{
	int decision = 0;
	std::cout << "-------MainMenu--------" << std::endl;
	std::cout << "1) host game" << std::endl;
	std::cout << "2) join game" << std::endl;
	std::cout << "3) hotseat" << std::endl;
	std::cout << "4) against AI" << std::endl;
	std::cin >> decision;

	switch (decision)
	{
		case 1:
		{
			stateManager->AddState((GameState*)(new InGame(stateManager, GAMETYPE::HOST)));
			stateManager->PopState();
			break;
		}
		case 2:
			stateManager->AddState((GameState*)(new InGame(stateManager, GAMETYPE::JOIN)));
			stateManager->PopState();
		{
			break;
		}
		case 3:
		{
			stateManager->AddState((GameState*)(new InGame(stateManager, GAMETYPE::HOTSEAT)));			
			stateManager->PopState();
			break;
		}
		case 4:
		{
			stateManager->AddState((GameState*)(new InGame(stateManager, GAMETYPE::AGAINSTAI)));
			stateManager->PopState();
			break;
		}
	default:
		break;
	}
}

void MainMenu::Uninitialize()
{

}

void MainMenu::Draw(sf::RenderWindow* window, TextManager* textManager)
{

}

void MainMenu::HandleInput(const sf::Event inputEvent, const sf::Vector2f mousePosition)
{

}
