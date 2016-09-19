#include "Game.h"

#include <iostream>

Game::Game()
{
	screenResolution = new sf::Vector2f(800.0f, 600.0f);

	bool firstWhite = false;

	//create chess table
	for (int i = 0; i < 64; i++)
	{			
		if (i % 8 == 0)
		{
			bool white = table[i - 1]->isWhite;
			table[i] = new Square(white);
			firstWhite = white;
		}
		else
		{
			if (firstWhite)
			{
				//white squares
				if (i % 2 == 0)
					table[i] = new Square(true);
				//black squares
				else
					table[i] = new Square(false);
			}
			else
			{
				//white squares
				if (i % 2 == 0)
					table[i] = new Square(false);
				//black squares
				else
					table[i] = new Square(true);
			}
		}
	}	



	//create chess pieces
	for (int i = 32; i > 0; i--)
	{

		if ( 7 < i && i < 24)
		{
			//player 1 pawns
			if (i > 15)
			{
				ChessPiece piece(ChessPieceType::pawn, 1);
				pieces.push_back(piece);
				continue;
			}
			//player 2 pawns
			else
			{
				ChessPiece piece(ChessPieceType::pawn, 2);
				pieces.push_back(piece);
			}
		}

		//rooks
		if (i > 12)
		{
			//player 1 rooks
			if (i > 14)
			{
				ChessPiece piece(ChessPieceType::rook, 1);
				pieces.push_back(piece);
			}
			//player 2 rook
			else
			{
				ChessPiece piece(ChessPieceType::rook, 2);
				pieces.push_back(piece);
			}
		}
























		//pawns
		if (i > 16)
		{
			//player 1 pawns
			if (i > 24)
			{
				ChessPiece piece(ChessPieceType::pawn, 1);
				pieces.push_back(piece);
			}
			//player 2 pawns
			else
			{
				ChessPiece piece(ChessPieceType::pawn, 2);
				pieces.push_back(piece);
			}
		}
		//rooks
		else if (i > 12)
		{
			//player 1 rooks
			if (i > 14 )
			{
				ChessPiece piece(ChessPieceType::rook, 1);
				pieces.push_back(piece);
			}
			//player 2 rook
			else
			{
				ChessPiece piece(ChessPieceType::rook, 2);
				pieces.push_back(piece);
			}
		}
		//knights
		else if (i > 8)
		{
			//player 1 knights
			if (i > 10)
			{
				ChessPiece piece(ChessPieceType::knight, 1);
				pieces.push_back(piece);
			}
			//player 2 knights
			else
			{
				ChessPiece piece(ChessPieceType::knight, 2);
				pieces.push_back(piece);
			}
		}
		//bishops
		else if (i > 4)
		{
			//player 1 bishops
			if (i > 6)
			{
				ChessPiece piece(ChessPieceType::bishop, 1);
				pieces.push_back(piece);
			}
			//player 2 bishops
			else
			{
				ChessPiece piece(ChessPieceType::bishop, 2);
				pieces.push_back(piece);
			}
		}
		//queens
		else if (i > 2)
		{
			//player 1 queens
			if (i > 3)
			{
				ChessPiece piece(ChessPieceType::queen, 1);
				pieces.push_back(piece);
			}
			//player 2 queens
			else
			{
				ChessPiece piece(ChessPieceType::queen, 2);
				pieces.push_back(piece);
			}
		}
		//kings
		else
		{
			//player 1 kings
			if (i > 1)
			{
				ChessPiece piece(ChessPieceType::king, 1);
				pieces.push_back(piece);
			}
			//player 2 kings
			else
			{
				ChessPiece piece(ChessPieceType::king, 2);
				pieces.push_back(piece);
			}
		}
	}


	//for each (ChessPiece piece in pieces)
	//{
	//	std::cout << piece.GetChessPieceType() << std::endl;
	//	std::cout << piece.player << std::endl;
	//}


window = new sf::RenderWindow(sf::VideoMode(screenResolution->x, screenResolution->y), "Tsakki");
}

Game::~Game()
{
	delete window;
	for (int i = 63; i >= 0; i--)
	{
		delete table[i];
	}
}

void Game::Initialize()
{
	int counter = 0;

	bool _break = false;
	//place all table pieces
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (_break)
				break;
			//std::cout << table[(1 + x) * (1 + y)]->sprite.getGlobalBounds().width * x << " " << table[(1 + x) * (1 + y)]->sprite.getGlobalBounds().height * y << std::endl;
			table[counter]->sprite.setPosition((table[counter]->sprite.getGlobalBounds().width * x) + 100.0f, (table[counter]->sprite.getGlobalBounds().height * y) +100.0f );
			std::cout << table[counter]->sprite.getPosition().x << " " << table[counter]->sprite.getPosition().y << std::endl;
			counter++;
			
			if (x == 8)
			_break = true;
			//table[(1 + x) * (1 + y)]
			
		}
	}

	//place all chess pieces
	for (int i = 0; i < pieces.size(); i++)
	{

	}

	////place all the chess board pieces
	//for (int y = 0; y < 8; y++)
	//{
	//	for (int x = 0; x < 8; x++)
	//	{
	//		//std::cout << table[(1 + x) * (1 + y)]->sprite.getGlobalBounds().width * x << " " << table[(1 + x) * (1 + y)]->sprite.getGlobalBounds().height * y << std::endl;

	//		table[(1 + x) * (1 + y)]->sprite.setPosition(table[(1 + x) * (1 + y)]->sprite.getGlobalBounds().width * x, table[(1 + x) * (1 + y)]->sprite.getGlobalBounds().height * y);
	//	}		
	//}


	for (int i = 0; i < 64; i++)
	{
		//std::cout << table[i]->sprite.getPosition().x << " " << table[i]->sprite.getPosition().y << std::endl;
	}

	//for each (Square* square in table)
	//{
	//

	//	//char pos[10];
	//	//sprintf_s(pos, "%f", square->sprite.getPosition().x);
	//	//sprintf_s(pos, "%f", square->sprite.getPosition().y);
	//	//printf("\n");
	//}
	//place chess pieces to their correct positions
	


}

void Game::Loop()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		this->Draw();
		window->display();
	}

}

void Game::Uninitialize()
{

}

void Game::Draw()
{	
	window->clear(sf::Color(0, 0, 150, 255));

	for each (Square* square in table)
	{
		window->draw(square->sprite);
	}

	//for each (ChessPiece piece in pieces)
	//{
	//	window->draw(piece.GetSprite());
	//}
}