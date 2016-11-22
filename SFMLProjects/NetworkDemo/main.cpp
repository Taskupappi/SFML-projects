
#include "SFML\Network.hpp"
#include <iostream>

//network
__int32 PackMove(char move[4]);

//not a host
void AskForPacket(sf::UdpSocket socket);

//init
void Initialize(sf::TcpSocket socket);

//ui

sf::IpAddress hostIP = "172.31.16.55";
unsigned short port = 35795;
int host = -1;
bool quit = false;


//int main()
//{
//	//sf::TcpSocket tcpSocket; 
//	//sf::Socket::Status status;
//
//	//Initialize(tcpSocket);
//
//	// = tcpSocket.connect(hostIP, port);
//	//if (status != sf::Socket::Done)
//	//{
//
//	//}
//
//	//bool quit = false;
//	//while (!quit)
//	//{ 
//	//	switch (host)
//	//	{
//	//	case 0:
//	//	{//is not host
//
//	//		char packetToSend[4];
//	//		__int32 packet = 0;
//
//	//		std::cout << "Give a packet to send" << std::endl;
//	//		std::cin >> packetToSend;
//
//	//		packet = PackMove(packetToSend);
//
//	//		//send the packet
//	//		//if (tcpSocket.send(&packet, sizeof(__int32), hostIP, port) != sf::Socket::Done)
//	//		//{
//	//		//}
//	//		break;
//	//	}	
//	//	case 1:
//	//	{//is host
//	//		
//	//		break;
//	//	}
//	//	default:
//	//		break;
//	//	}
//
//	//}
//
//	//char move1[4];
//	//move1[0] = 'a';
//	//move1[1] = '1';
//	//move1[2] = 'a';
//	//move1[3] = '2';
//	//int packedMove;
//	//packedMove = PackMove(move1);
//
//	return 0;
//}

int main()
{
	sf::TcpSocket tcpSocket;
	sf::Socket::Status socketStatus;
	//for server only
	sf::TcpListener listener;
	sf::TcpSocket client;

	std::cout << "are you host? 1 = yes, 2 = no" << std::endl;
	std::cin >> host;

	switch (host)
	{
		case 1:
		{//host
			socketStatus = tcpSocket.connect(hostIP, port);
			if (socketStatus != sf::Socket::Done)
			{
				return 0;
			}

			if (listener.listen(port) != sf::Socket::Done)
			{

			}

			if (listener.accept(client) != sf::Socket::Done)
			{

			}

			break;
		}
		case 2:
		{//not a host
			std::cout << "give hosts ip" << std::endl;
			std::cin >> hostIP;

			std::cout << "give hosts port" << std::endl;
			std::cin >> port;

			socketStatus = tcpSocket.connect(hostIP, port);
			if (socketStatus != sf::Socket::Done)
			{
				return 0;
			}



			break;
		}
		default:
			break;
	}
		

	while (!quit)
	{
		switch (host)
		{
		case 1:
		{//host
			//wait for data
			__int32 receivedMove;
			size_t received;

			if (tcpSocket.receive(&receivedMove, sizeof(__int32), received) == sf::Socket::Done)
			{

			}

			std::cout << "Received " << received << " bytes" << std::endl;

			//__int32* move;

			//move = Decrypt(receivedMove);

			break;
		}
		case 2:
		{//not a host
			//ask data to send
			char move[4];
			__int32 moveInt;

			std::cout << "give move" << std::endl;
			std::cin >> move;

			moveInt = PackMove(move);

			if (tcpSocket.send(&moveInt, sizeof(__int32)))
			{
				return 0;
			}

			break;
		}
		default:
			break;
		}
	}
			
}

__int32 PackMove(char move[4])
{		
	//turn char formatted move into an integer
	__int32 tempPacket = 0;
	for (int i = 0; i != 4; ++i) 
	{
		tempPacket += move[i] << (24 - i * 8);
	}

	//turn bits
	tempPacket = ~tempPacket;

	return tempPacket;
}

char* Decrypt(__int32 toBeDecryptedMove)
{
	char* move = new char[4];

	return nullptr;
}

