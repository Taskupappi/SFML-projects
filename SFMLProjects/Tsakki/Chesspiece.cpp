#include "ChessPiece.h"

ChessPiece::ChessPiece(ChessPieceType const _type, int const _player, sf::Vector2u _tablePosition)
{
	//Sprite stuff
	//texture.loadFromFile("ChessPieceSprite.png");
	texture.loadFromFile("chesspiece.png");
	sprite.setTexture(texture);

	//owner
	player = _player;

	switch (_type)
	{
		case pawn:
		{
			if (player == 2)
			{
				sprite.setTextureRect(sf::IntRect(50, 10, 10, 10));
				//sprite.setTextureRect(sf::IntRect(1667, 667, 333, 333));
				
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(50, 0, 10, 10));
				//sprite.setTextureRect(sf::IntRect(1667, 333, 333, 333));
			}			
			break;
		}			
		case knight:
		{
			if (player == 2)
			{
				sprite.setTextureRect(sf::IntRect(10, 10, 10, 10));
				//sprite.setTextureRect(sf::IntRect(1000, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(10, 0, 10, 10));
				//sprite.setTextureRect(sf::IntRect(1000, 333, 333, 333));
			}
			break;
		}
		case rook:	
		{
			if (player == 2)
			{
				sprite.setTextureRect(sf::IntRect(0, 10, 10, 10));
				//sprite.setTextureRect(sf::IntRect(1333, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
				//sprite.setTextureRect(sf::IntRect(1333, 333, 333, 333));
			}
			break;
		}
		case bishop:
		{
			if (player == 2)
			{
				sprite.setTextureRect(sf::IntRect(20, 10, 10, 10));
				//sprite.setTextureRect(sf::IntRect(667, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(20, 0, 10, 10));
				//sprite.setTextureRect(sf::IntRect(667, 333, 333, 333));
			}
			break;
		}
		case queen:
		{
			if (player == 2)
			{
				sprite.setTextureRect(sf::IntRect(30, 10, 10, 10));
				//sprite.setTextureRect(sf::IntRect(333, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(30, 0, 10, 10));
				//sprite.setTextureRect(sf::IntRect(333, 333, 333, 333));
			}
			break;
		}
		case king:
		{
			if (player == 2)
			{
				sprite.setTextureRect(sf::IntRect(40, 10, 10, 10));
				//sprite.setTextureRect(sf::IntRect(0, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(40, 0, 10, 10));
				//sprite.setTextureRect(sf::IntRect(0, 333, 333, 333));
			}
			break;
		}
		default:
			break;
	}

	sprite.setScale(5.0f, 5.0f);
	sprite.setOrigin(5.0f, 5.0f);
	//sprite.setOrigin(166.5f, 166.5f);
	type = _type;

	
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
