#ifndef HEX_H
#define HEX_H

#include "SFML\Graphics.hpp"

enum HEXTYPE
{
	DenseForest,
	LightForest,
	ClearGrass,

};

class Hex : public sf::Transformable
{
public:
	Hex();
	~Hex();
	void setTexture(HEXTYPE type);
	sf::CircleShape* GetShape(){ return hexagon; };
private:
	sf::CircleShape* hexagon;

};

#endif
