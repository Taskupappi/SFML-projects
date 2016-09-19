#include "Game.h"

#include <iostream>

Game::Game()
{
	screenResolution = new sf::Vector2u(800, 600);
		
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			//check the end of the last row
			
			//if y - 1 is not below zero we have more than one row
			if (y - 1 > -1)
			{
				bool lastIsWhite = table[7][y - 1]->isWhite;
				if (lastIsWhite)
				{
					//white squares
					if (x % 2 == 0)
						table[x][y] = new Square(true);
					//black squares
					else
						table[x][y] = new Square(false);
				}
				else
				{
					//white squares
					if (x % 2 == 0)
						table[x][y] = new Square(false);
					//black squares
					else
						table[x][y] = new Square(true);
				}
			}
			//first row
			else
			{
				//white squares
				if (x % 2 == 0)
					table[x][y] = new Square(true);
				//black squares
				else
					table[x][y] = new Square(false);
			}
		}
	}

	//bool firstWhite = false;

	////create chess table
	//for (int i = 0; i < 64; i++)
	//{			
	//	if (i % 8 == 0)
	//	{
	//		bool white = table[i - 1]->isWhite;
	//		table[i] = new Square(white);
	//		firstWhite = white;
	//	}
	//	else
	//	{
	//		if (firstWhite)
	//		{
	//			//white squares
	//			if (i % 2 == 0)
	//				table[i] = new Square(true);
	//			//black squares
	//			else
	//				table[i] = new Square(false);
	//		}
	//		else
	//		{
	//			//white squares
	//			if (i % 2 == 0)
	//				table[i] = new Square(false);
	//			//black squares
	//			else
	//				table[i] = new Square(true);
	//		}
	//	}
	//}	
	
	//player 1
	for (int i = 0; i < 16; i++)
	{
		if (i < 8)
		{
			//rooks
			if (i == 0 || 7)
			{
				pieces[0][i] = new ChessPiece(ChessPieceType::rook, 1, sf::Vector2i(i, 0));
			}
			//knights
			else if (i == 1 || i == 6)
			{
				pieces[0][i] = new ChessPiece(ChessPieceType::knight, 1, sf::Vector2i(i, 0));
			}
			//bishops
			else if (i == 2 || i == 5)
			{
				pieces[0][i] = new ChessPiece(ChessPieceType::bishop, 1, sf::Vector2i(i, 0));
			}
			//Queen
			else if (i == 3)
			{
				pieces[0][i] = new ChessPiece(ChessPieceType::queen, 1, sf::Vector2i(i, 0));
			}
			//King
			else if (i == 4)
			{
				pieces[0][i] = new ChessPiece(ChessPieceType::king, 1, sf::Vector2i(i, 0));
			}
		}	
		//pawns
		else
		{
			pieces[0][i] = new ChessPiece(ChessPieceType::pawn, 1, sf::Vector2i(i, 1));
		}
	}

	//player 2
	for (int i = 0; i < 16; i++)
	{
		if (i < 8)
		{
			//rooks
			if (i == 0 || 7)
			{
				pieces[1][i] = new ChessPiece(ChessPieceType::rook, 2, sf::Vector2i(i, 6));
			}
			//knights
			else if (i == 1 || i == 6)
			{
				pieces[1][i] = new ChessPiece(ChessPieceType::knight, 2, sf::Vector2i(i, 6));
			}
			//bishops
			else if (i == 2 || i == 5)
			{
				pieces[1][i] = new ChessPiece(ChessPieceType::bishop, 2, sf::Vector2i(i, 6));
			}
			//Queen
			else if (i == 3)
			{
				pieces[1][i] = new ChessPiece(ChessPieceType::queen, 2, sf::Vector2i(i, 6));
			}
			//King
			else if (i == 4)
			{
				pieces[1][i] = new ChessPiece(ChessPieceType::king, 2, sf::Vector2i(i, 6));
			}
		}
		//pawns
		else
		{
			pieces[1][i] = new ChessPiece(ChessPieceType::pawn, 2, sf::Vector2i(i, 7));
		}
	}


	/*
	////create chess pieces
	//for (int i = 32; i > 0; i--)
	//{
	//	////pawns
	//	//if (i > 16)
	//	//{
	//	//	//player 1 pawns
	//	//	if (i > 24)
	//	//	{
	//	//		ChessPiece* piece = new ChessPiece(ChessPieceType::pawn, 1);
	//	//		pieces[0][i] = piece;
	//	//	}
	//	//	//player 2 pawns
	//	//	else
	//	//	{
	//	//		ChessPiece* piece = new ChessPiece(ChessPieceType::pawn, 2);
	//	//		pieces[i][] = piece;
	//	//	}
	//	//}

	//	//player 1

	//	//player 2



	//	//if ( 7 < i && i < 24)
	//	//{
	//	//	//player 1 pawns
	//	//	if (i > 15)
	//	//	{
	//	//		ChessPiece piece(ChessPieceType::pawn, 1);
	//	//		pieces.push_back(piece);
	//	//		continue;
	//	//	}
	//	//	//player 2 pawns
	//	//	else
	//	//	{
	//	//		ChessPiece piece(ChessPieceType::pawn, 2);
	//	//		pieces.push_back(piece);
	//	//	}
	//	//}

	//	////rooks
	//	//if (i > 12)
	//	//{
	//	//	//player 1 rooks
	//	//	if (i > 14)
	//	//	{
	//	//		ChessPiece piece(ChessPieceType::rook, 1);
	//	//		pieces.push_back(piece);
	//	//	}
	//	//	//player 2 rook
	//	//	else
	//	//	{
	//	//		ChessPiece piece(ChessPieceType::rook, 2);
	//	//		pieces.push_back(piece);
	//	//	}
	//	//}

	//	//pawns
	//	if (i > 16)
	//	{
	//		//player 1 pawns
	//		if (i > 24)
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::pawn, 1);
	//			pieces[i] = piece;
	//		}
	//		//player 2 pawns
	//		else
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::pawn, 2);
	//			pieces[i] = piece;
	//		}
	//	}
	//	//rooks
	//	else if (i > 12)
	//	{
	//		//player 1 rooks
	//		if (i > 14 )
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::rook, 1);
	//			pieces[i] = piece;
	//		}
	//		//player 2 rook
	//		else
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::rook, 2);
	//			pieces[i] = piece;
	//		}
	//	}
	//	//knights
	//	else if (i > 8)
	//	{
	//		//player 1 knights
	//		if (i > 10)
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::knight, 1);
	//			pieces[i] = piece;
	//		}
	//		//player 2 knights
	//		else
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::knight, 2);
	//			pieces[i] = piece;
	//		}
	//	}
	//	//bishops
	//	else if (i > 4)
	//	{
	//		//player 1 bishops
	//		if (i > 6)
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::bishop, 1);
	//			pieces[i] = piece;
	//		}
	//		//player 2 bishops
	//		else
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::bishop, 2);
	//			pieces[i] = piece;
	//		}
	//	}
	//	//queens
	//	else if (i > 2)
	//	{
	//		//player 1 queens
	//		if (i > 3)
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::queen, 1);
	//			pieces[i] = piece;
	//		}
	//		//player 2 queens
	//		else
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::queen, 2);
	//			pieces[i] = piece;
	//		}
	//	}
	//	//kings
	//	else
	//	{
	//		//player 1 kings
	//		if (i > 1)
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::king, 1);
	//			pieces[i] = piece;
	//		}
	//		//player 2 kings
	//		else
	//		{
	//			ChessPiece* piece = new ChessPiece(ChessPieceType::king, 2);
	//			pieces[i] = piece;
	//		}
	//	}
	//}
*/
	
	window = new sf::RenderWindow(sf::VideoMode(screenResolution->x, screenResolution->y), "Tsakki");
}

Game::~Game()
{
	delete window;

	//for each (ChessPiece* piece in pieces)
	//{
	//	delete piece;
	//}
}

void Game::Initialize()
{
	//place all table pieces
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			table[x][y]->sprite.setPosition((table[x][y]->sprite.getGlobalBounds().width * x) + 100.0f, (table[x][y]->sprite.getGlobalBounds().height * y) + 100.0f);
			std::cout << table[x][y]->sprite.getPosition().x << " " << table[x][y]->sprite.getPosition().y << std::endl;
		}
	}

	//place all pieces
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 10; y++)
		{


			//pieces[x][y]->GetSprite().setPosition((table[x][y]->sprite.getGlobalBounds().width * x) + 100.0f, (table[x][y]->sprite.getGlobalBounds().height * y) + 100.0f);
			//piece->GetSprite().setPosition(sf::Vector2f(table[piece->tablePosition.x][piece->tablePosition.y]->sprite.getPosition().x, table[piece->tablePosition.x][piece->tablePosition.y]->sprite.getPosition().x)); // = table[x][y]->sprite.getPosition();
			//pieces[i][y]->GetSprite().setPosition(sf::Vector2f(table[pieces[i][y]->tablePosition.x][pieces[i][y]->tablePosition.y]->sprite.getPosition().x, table[pieces[i][y]->tablePosition.x][pieces[i][y]->tablePosition.y]->sprite.getPosition().y));
		}
	}
	
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
	//delete all table pieces
	for (int x = 1; x > -1; x--)
	{
		for (int y = 7; y > -1; y--)
		{
			delete pieces[x][y];
		}
	}

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			delete table[x][y];
		}
	}


}

void Game::Draw()
{	
	window->clear(sf::Color(0, 0, 150, 255));

	//draw all chess table squares
	for each (Square* square in table)
	{
		window->draw(square->sprite);
	}

	//highlight all the squares the chess piece could move to
	/*for each()
	{

	}*/

	//draw all the pieces on the chess table
	for each (ChessPiece* piece in pieces)
	{
		window->draw(piece->GetSprite());
	}
}