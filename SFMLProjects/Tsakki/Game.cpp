#include "Game.h"

#include <iostream>

Game::Game()
{
	//create chess table
	for (int i = 0; i < 64; i++)
	{
		//white squares
		if (i < 32)
		{
			
		}

		//black squares
		else
		{

		}
	}

	//create chess pieces
	//for (int i = 32; i > 0; i--)
	//{
	//	//pawns
	//	if (i > 16)
	//	{
	//		//player 1 pawns
	//		if (i > 24)
	//		{
	//			ChessPiece piece(ChessPieceType::pawn, 1);
	//			pieces.push_back(piece);
	//		}
	//		//player 2 pawns
	//		else
	//		{
	//			ChessPiece piece(ChessPieceType::pawn, 2);
	//			pieces.push_back(piece);
	//		}
	//	}
	//	//rooks
	//	else if (i > 12)
	//	{
	//		//player 1 rooks
	//		if (i > 14 )
	//		{
	//			ChessPiece piece(ChessPieceType::rook, 1);
	//			pieces.push_back(piece);
	//		}
	//		//player 2 rook
	//		else
	//		{
	//			ChessPiece piece(ChessPieceType::rook, 2);
	//			pieces.push_back(piece);
	//		}
	//	}
	//	//knights
	//	else if (i > 8)
	//	{
	//		//player 1 knights
	//		if (i > 10)
	//		{
	//			ChessPiece piece(ChessPieceType::knight, 1);
	//			pieces.push_back(piece);
	//		}
	//		//player 2 knights
	//		else
	//		{
	//			ChessPiece piece(ChessPieceType::knight, 2);
	//			pieces.push_back(piece);
	//		}
	//	}
	//	//bishops
	//	else if (i > 4)
	//	{
	//		//player 1 bishops
	//		if (i > 6)
	//		{
	//			ChessPiece piece(ChessPieceType::bishop, 1);
	//			pieces.push_back(piece);
	//		}
	//		//player 2 bishops
	//		else
	//		{
	//			ChessPiece piece(ChessPieceType::bishop, 2);
	//			pieces.push_back(piece);
	//		}
	//	}
	//	//queens
	//	else if (i > 2)
	//	{
	//		//player 1 queens
	//		if (i > 3)
	//		{
	//			ChessPiece piece(ChessPieceType::queen, 1);
	//			pieces.push_back(piece);
	//		}
	//		//player 2 queens
	//		else
	//		{
	//			ChessPiece piece(ChessPieceType::queen, 2);
	//			pieces.push_back(piece);
	//		}
	//	}
	//	//kings
	//	else
	//	{
	//		//player 1 kings
	//		if (i > 1)
	//		{
	//			ChessPiece piece(ChessPieceType::king, 1);
	//			pieces.push_back(piece);
	//		}
	//		//player 2 kings
	//		else
	//		{
	//			ChessPiece piece(ChessPieceType::king, 2);
	//			pieces.push_back(piece);
	//		}
	//	}
	//}

	//for each (ChessPiece piece in pieces)
	//{
	//	std::cout << piece.GetChessPieceType() << std::endl;
	//	std::cout << piece.player << std::endl;
	//}


	window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");
}

Game::~Game()
{
	delete window;
}

void Game::Initialize()
{
	//place all the chess board pieces

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
	//for each (ChessPiece piece in pieces)
	//{
	//	window->draw(piece.GetSprite());
	//}

	for each (ChessPiece piece in pieces)
	{
		window->draw(piece.GetSprite());
	}
}