#include "TextManager.h"

TextManager::TextManager()
{
	if (!font.loadFromFile("Thempo New St.ttf"))
	{
		printf("error while loading font");
	}
}

TextManager::~TextManager()
{
	//texts.clear();

	if (!texts.empty())
	{
		for (std::vector<std::pair<TEXTTYPE, sf::Text*>>::iterator text = texts.begin(); text != texts.end(); text++)
		{
			delete (*text).second;
			text = texts.erase(text);

			if (text == texts.end())
				break;
		}

		texts.clear();
	}	
}

void TextManager::AddText(const TEXTTYPE _textType, const std::string _text)
{
	//remove any duplicates of player turn info text
	if (TEXTTYPE::PLAYERTURN == _textType)
	{
		if (!texts.empty())
		{
			for (std::vector<std::pair<TEXTTYPE, sf::Text*>>::iterator text = texts.begin(); text != texts.end(); text++)
			{
				if ((*text).first == TEXTTYPE::PLAYERTURN)
				{
					delete (*text).second;					
					text = texts.erase(text);
				}

				if (text == texts.end())
				{
					break;
				}
			}
		}		
	}

	sf::Text* text = new sf::Text();
	text->setFont(font);
	text->setString(_text);
	text->setCharacterSize(24);
	text->setColor(sf::Color::White);
	text->setStyle(sf::Text::Bold);
	text->setOrigin(text->getLocalBounds().left + text->getLocalBounds().width * 0.5f, text->getLocalBounds().top + text->getLocalBounds().height * 0.5f);
	texts.push_back(std::make_pair(_textType, text));
}

void TextManager::Draw(sf::RenderWindow* _window)
{
	for (std::vector<std::pair<TEXTTYPE, sf::Text*>>::iterator text = texts.begin(); text != texts.end(); text++)
	{
		switch ((*text).first)
		{
			case TEXTTYPE::PLAYERTURN:
			{
				//(*text).second->setpos
				(*text).second->setPosition(_window->getDefaultView().getSize().x * 0.5f, _window->getDefaultView().getSize().y * 0.1f);
				_window->draw(*(*text).second);
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