#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
	GameState(){};
	~GameState(){};

	//GameState core
	virtual void Initialize(){};
	virtual void Loop(sf::RenderWindow* window){};
	virtual void Uninitialize(){};
	virtual void Draw(){};
	virtual void HandleInput(){};
};

#endif
