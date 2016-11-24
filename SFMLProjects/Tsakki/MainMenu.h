#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"
#include "TextManager.h"

class MainMenu : public GameState
{
public:
	MainMenu(GameStateManager* stateManager);
	~MainMenu();

	//InGame state core
	void Initialize();
	void Loop(sf::RenderWindow* window, const sf::Vector2f mousePosition, TextManager* textManager);
	void Uninitialize();
	void Draw(sf::RenderWindow* window, TextManager* textManager);
	void HandleInput(const sf::Event inputEvent, const sf::Vector2f mousePosition);
private:

};

#endif