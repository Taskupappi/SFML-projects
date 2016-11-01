#include "TextManager.h"

TextManager::TextManager()
{
	if (!font.loadFromFile("Thempo New St.ttf"));
	{
		printf("error while loading font");
	}
}

TextManager::~TextManager()
{
	texts.clear();
}

void TextManager::AddText(const TEXTTYPE _textType, const std::string _text)
{
	//remove any duplicates of player turn info text
	if (TEXTTYPE::PLAYERTURN == _textType)
	{
		if (!texts.empty())
		{
			for (std::vector<std::pair<TEXTTYPE, sf::Text*>>::iterator text = texts.end() - 1; text != texts.begin() - 1; text--)
			{
				if ((*text).first == TEXTTYPE::PLAYERTURN)
				{
					delete (*text).second;					
					texts.erase(text);
				}

				//prevent loop from breaking
				if (text == texts.begin())
				{
					break;
				}
			}
		}		
	}

	sf::Text* text = new sf::Text;
	text->setFont(font);
	text->setString(_text);
	text->setCharacterSize(24);
	text->setColor(sf::Color::White);
	text->setStyle(sf::Text::Bold);
	texts->push_back(std::make_pair(_textType, text));
}

void TextManager::Draw(sf::RenderWindow* _window)
{
	for (std::vector<std::pair<TEXTTYPE, sf::Text*>>::iterator text = texts.begin(); text != texts.end(); text++)
	{
		switch ((*text).first)
		{
			case TEXTTYPE::PLAYERTURN:
			{
				(*text).second.setPosition(_window->getSize().x * 0.5f, _window->getSize().y * 0.1f);
				_window->draw((*text).second);
				break;
			}
			case TEXTTYPE::MOVEINFO:
			{
				break;
			}
			default:
				break;
		}
	}
}