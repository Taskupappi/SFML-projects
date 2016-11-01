#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

//#include "SFML\Graphics\Font.hpp"
//#include "SFML\Graphics\Text.hpp"
#include "SFML\Graphics.hpp"
#include <vector>

enum TEXTTYPE
{
	PLAYERTURN,
	MOVEINFO,
};

class TextManager
{
public:

	TextManager();
	~TextManager();
	void Draw(sf::RenderWindow* window);
	void AddText(const TEXTTYPE textType, const std::string text);

	//texts
	std::vector<std::pair<TEXTTYPE, sf::Text*>> texts;
private:
	sf::Font font;
};

#endif
