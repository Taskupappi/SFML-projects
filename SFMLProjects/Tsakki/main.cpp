#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	Game game;
	
	game.Initialize();
	game.Loop();
	//game.Uninitialize();
		
	return 0;
}