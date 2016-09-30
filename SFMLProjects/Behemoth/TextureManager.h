#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SFML\Graphics\Texture.hpp"
#include <vector>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void LoadTexture(const std::string textureName);
	sf::Texture* GetTexture(const std::string textureName);
private:

	std::vector<sf::Texture> textures;
};

#endif
