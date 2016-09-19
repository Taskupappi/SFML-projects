#include "ChessPiece.h"

ChessPiece::ChessPiece(ChessPieceType const _type, int const _player, sf::Vector2i _tablePosition)
{
	//Sprite stuff
	texture.loadFromFile("ChessPieceSprite.png");
	sprite.setTexture(texture);

	switch (_type)
	{
		case pawn:
		{
			if (player == 1)
			{
				sprite.setTextureRect(sf::IntRect(1667, 667, 333, 333));
				
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(1667, 333, 333, 333));
			}			
			break;
		}			
		case knight:
		{
			if (player == 1)
			{
				sprite.setTextureRect(sf::IntRect(1000, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(1000, 333, 333, 333));
			}
			break;
		}
		case rook:	
		{
			if (player == 1)
			{
				sprite.setTextureRect(sf::IntRect(1333, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(1333, 333, 333, 333));
			}
			break;
		}
		case bishop:
		{
			if (player == 1)
			{
				sprite.setTextureRect(sf::IntRect(667, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(667, 333, 333, 333));
			}
			break;
		}
		case queen:
		{
			if (player == 1)
			{
				sprite.setTextureRect(sf::IntRect(333, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(333, 333, 333, 333));
			}
			break;
		}
		case king:
		{
			if (player == 1)
			{
				sprite.setTextureRect(sf::IntRect(0, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(0, 333, 333, 333));
			}
			break;
		}
		default:
			break;
	}

	sprite.setOrigin(166.5f, 166.5f);
	type = _type;

	//owner
	player = _player;

	//table position
	tablePosition = _tablePosition;
}

ChessPiece::~ChessPiece()
{

}


const char* ChessPiece::GetChessPieceType()
{
	switch (type)
	{
	case pawn: return "pawn";
	case knight: return "knight";
	case rook: return "rook";
	case bishop: return "bishop";
	case queen: return "queen";
	case king: return "king";
	default: return "";
	}
}
