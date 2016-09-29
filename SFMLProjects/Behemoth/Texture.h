#ifndef TEXTURE_H
#define TEXTURE_H

#include "SFML\Graphics.hpp"
#include "SFML\Graphics\Texture.hpp"

class Texture
{
public:
	Texture(const std::string textureName)
		: name(textureName) 
	{ 	
		std::string texturePath = "Assets/Sprites/";
		texturePath.append(textureName);
		texture.loadFromFile(texturePath);
	};
	~Texture();
private:
	sf::Texture texture;
	const std::string name;
};

#endif
