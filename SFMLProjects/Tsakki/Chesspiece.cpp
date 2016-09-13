#include "ChessPiece.h"

ChessPiece::ChessPiece(ChessPieceType const _type, bool _player1)
{

	player1 = _player1;

	texture.loadFromFile("ChessPieceSprite");
	sprite.setTexture(texture);
	sprite.setOrigin(333.0f / 2.0f, 333.0f / 2.0f);


	switch (_type)
	{
		case pawn:
		{
			if (player1)
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
			if (player1)
			{
				sprite.setTextureRect(sf::IntRect(1000, 667, 333, 333));
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(1000, 333, 333, 333));
			}
			break;
		}
			break;
		case rook:	
		{
			if (player1)
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
			if (player1)
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
			if (player1)
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
			if (player1)
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
}

ChessPiece::~ChessPiece()
{

}

