#include "Game.h"

#include <iostream>

Game::Game()
{
	screenResolution = new sf::Vector2u(800, 600);
	
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
	table.Initialize();	
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

			HandleInput();
		}

		window->clear();
		this->Draw();
		window->display();
	}

}

void Game::Uninitialize()
{
	table.Uninitialize();
}

void Game::Draw()
{	
	window->clear(sf::Color(0, 0, 150, 255));

	table.Draw(window);
}

void Game::HandleInput()
{
	//mouse position
	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	system("cls");
	std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
	
	table.HandleInput(mousePosition);

}