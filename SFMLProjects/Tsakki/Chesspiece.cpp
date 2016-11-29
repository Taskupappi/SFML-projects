#include "ChessPiece.h"

ChessPiece::ChessPiece(ChessPieceType const _type, Player const _player)
{
	//Sprite stuff
	//texture.loadFromFile("ChessPieceSprite.png");
	texture.loadFromFile("Chess_Pieces_Sprite.png");
	sprite.setTexture(texture);

	//owner
	player = _player;

	switch (_type)
	{
		case pawn:
		{
			if (player.color == COLOR::WHITE)
			{
				sprite.setTextureRect(sf::IntRect(225, 0, 45, 45));
				//sprite.setTextureRect(sf::IntRect(1667, 667, 333, 333));				
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(225, 45, 45, 45));
				//sprite.setTextureRect(sf::IntRect(1667, 333, 333, 333));
			}			
			break;
		}			
		case knight:
		{
			if (player.color == COLOR::WHITE)
			{
				sprite.setTextureRect(sf::IntRect(135, 0, 45, 45));
				//sprite.setTextureRect(sf::IntRect(1000, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(135, 45, 45, 45));
				//sprite.setTextureRect(sf::IntRect(1000, 333, 333, 333));
			}
			break;
		}
		case rook:	
		{
			if (player.color == COLOR::WHITE)
			{
				sprite.setTextureRect(sf::IntRect(180, 0, 45, 45));
				//sprite.setTextureRect(sf::IntRect(1333, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(180, 45, 45, 45));
				//sprite.setTextureRect(sf::IntRect(1333, 333, 333, 333));
			}
			break;
		}
		case bishop:
		{
			if (player.color == COLOR::WHITE)
			{
				sprite.setTextureRect(sf::IntRect(90, 0, 45, 45));
				//sprite.setTextureRect(sf::IntRect(667, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(90, 45, 45, 45));
				//sprite.setTextureRect(sf::IntRect(667, 333, 333, 333));
			}
			break;
		}
		case queen:
		{
			if (player.color == COLOR::WHITE)
			{
				sprite.setTextureRect(sf::IntRect(45, 0, 45, 45));
				//sprite.setTextureRect(sf::IntRect(333, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(45, 45, 45, 45));
				//sprite.setTextureRect(sf::IntRect(333, 333, 333, 333));
			}
			break;
		}
		case king:
		{
			if (player.color == COLOR::WHITE)
			{
				sprite.setTextureRect(sf::IntRect(0, 0, 45, 45));
				//sprite.setTextureRect(sf::IntRect(0, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(0, 45, 45, 45));
				//sprite.setTextureRect(sf::IntRect(0, 333, 333, 333));
			}
			break;
		}
		default:
			break;
	}

	sprite.setScale(1.00f, 1.00f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	//sprite.setOrigin(166.5f, 166.5f);
	type = _type;

	
	//table position
	tablePosition = sf::Vector2i(-12, -12);
}

ChessPiece::~ChessPiece()
{
	allMoves.clear();
	checkingMoves.clear();
	possibleMoves.clear();
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
