#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <thread>
#include <mutex>

#include "Game.h"

int main()
{
	Game game;
	
	game.Initialize();
	game.Loop();
	game.Uninitialize();
		
	return 0;
}










//
//#include <iostream>
//
////network
//char* Decrypt(__int32 toBeDecryptedMove);
//__int32 PackMove(const char move[]);
//
////not a host
//void AskForPacket(sf::UdpSocket socket);
//
////ui
//sf::IpAddress hostIP = "172.31.16.55";
//unsigned short port = 35795;
//int host = -1;
//bool quit = false;
//
//char buffer[100];
////__int32 buffer;
//std::size_t received;
//
//sf::TcpSocket tcpSocket;
//
//std::thread receiverThread;
//std::thread senderThread;
//std::thread mainThread;
//
//
//struct TEST
//{
//	std::string KisseCount;
//};
//
//
//int main()
//{
//	
//
//
//	hostIP = sf::IpAddress::getLocalAddress();
//	std::string text = "connected to ";
//	char connectionType, mode;
//
//	char testMove[4];
//	testMove[0] = 'e';
//	testMove[1] = '4';
//	testMove[2] = 'e';
//	testMove[3] = '5';
//
//	__int32 moveTestInt = PackMove(testMove);
//
//	std::cout << "Enter (s) for server or (c) for client" << std::endl;
//	std::cin >> connectionType;
//
//	if (connectionType == 's')
//	{
//		sf::TcpListener listener;
//		listener.listen(port);
//		listener.accept(tcpSocket);
//		text += "server";
//		mode = 's';
//	}
//	else if (connectionType == 'c')
//	{
//		//std::string tempIP = (std::string)sf::IpAddress::getLocalAddress();
//
//		std::string tempIP = "";
//		std::cout << "Give server address" << std::endl;
//		std::cin >> tempIP;
//		
//		sf::Time time;
//
//		time.asSeconds();
//
//		tcpSocket.connect(tempIP, port);
//		
//
//		text += "client";
//		mode = 'r';
//	}
//	else
//	{
//		return 0;
//	}
//
//	text = "rum8";
//
//	tcpSocket.send(text.c_str(), text.length() + 1);
//
//	tcpSocket.receive(&buffer, sizeof(buffer), received);
//
//	std::cout << buffer << std::endl;
//
//	bool done = false;
//
//	while (!done)
//	{ 
//		sf::Packet _packet;
//
//		if (mode == 's') //send
//		{
//
//			TEST test;
//
//			std::getline(std::cin, test.KisseCount);
//			//__int32 move = PackMove(text.c_str());
//			//std::cout << "move: " << &move << std::endl;
//			//tcpSocket.send(&move, sizeof(move));
//		
//			_packet << test.KisseCount;
//
//			tcpSocket.send(_packet);
//			
//			//tcpSocket.send(text.c_str(), text.length() + 1);
//			mode = 'r';
//		}
//		else if (mode == 'r') //receive
//		{
//			TEST answer;
//			
//			//tcpSocket.receive(textBuffer, sizeof(textBuffer), received);	
//			tcpSocket.receive(_packet);
//			if (_packet >> answer.KisseCount)
//			{
//				//std::cout << "Received: " << textBuffer << std::endl;
//				std::cout << "Received: " << answer.KisseCount << std::endl;
//				mode = 's';
//			}		
//		}
//	}
//}
//
//char* Decrypt(__int32 toBeDecryptedMove)
//{
//	toBeDecryptedMove = ~toBeDecryptedMove;
//
//	char move[4];
//	move[0] = (toBeDecryptedMove >> 24);
//	move[1] = (toBeDecryptedMove >> 16);
//	move[2] = (toBeDecryptedMove >> 8);
//	move[3] = (toBeDecryptedMove >> 0);
//
//	return move;
//}
//
//__int32 PackMove(const char move[])
//{
//	//turn char formatted move into an integer
//	__int32 tempPacket = 0;
//
//	tempPacket = (move[0] << 24) + (move[1] << 16) + (move[2] << 8) + (move[3]);
//
//	tempPacket = ~tempPacket;
//
//	return tempPacket;
//}
