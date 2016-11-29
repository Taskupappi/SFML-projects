#include "Network.h"

#include <iostream>

Network::Network(const bool _isHost)
	: isHost(_isHost)
{	
}

Network::~Network()
{
}

void Network::Initialize()
{
	if (isHost)
	{
		hostIP = sf::IpAddress::getLocalAddress();
		listener.listen(port);
		listener.accept(tcpSocket);
	}
	else
	{
		std::string serverIP;
		std::cout << "Give IP address to connect" << std::endl;
		std::cin >> serverIP;

		setHostIP(serverIP);
		
		sf::Time connectionTimeoutTime = sf::seconds(10.0f);

		if (!tcpSocket.connect(serverIP, port, connectionTimeoutTime))
		{
			std::cout << "could not connect to the server!" << std::endl;
			Initialize();
		}
	}
}

void Network::setHostIP(const std::string _hostIP)
{
	hostIP = _hostIP;
}

void Network::setPort(const unsigned short _port)
{
	port = _port;
}

void Network::SavePacket(const NetworkPacket _receivedPacket)
{
	savedPackets.push_back(_receivedPacket);
}

void Network::SendHostColor(const bool _isWhite)
{
	sf::Packet packetToSend;

	NetworkPacket data;
	data.packetType = PACKETTYPE::HOSTCOLOR;
	data.moveData = 0;
	
	if (_isWhite)
	{
		data.message = "isWhite";
	}
	else
	{
		data.message = "notWhite";
	}

	packetToSend << data;

	tcpSocket.send(packetToSend);
}

sf::Uint32 Network::PackMove(const char _move[])
{
	//turn char formatted move into an integer
	sf::Uint32 packedMove = 0;
	packedMove << (_move[0] << 24) + (_move[0] << 16) + (_move[0] << 8) + (_move[0]);

	packedMove = ~packedMove;

	return packedMove;
}

std::string Decrypt(sf::Int32 _toBeEncryptedMove)
{
	_toBeEncryptedMove = ~_toBeEncryptedMove;
	
	std::string decryptedMove = "";
	decryptedMove = (_toBeEncryptedMove >> 24);
	decryptedMove = (_toBeEncryptedMove >> 16);
	decryptedMove = (_toBeEncryptedMove >> 8);
	decryptedMove = (_toBeEncryptedMove >> 0);


	//char move[4];
	//move[0] = (_toBeEncryptedMove >> 24);
	//move[1] = (_toBeEncryptedMove >> 16);
	//move[2] = (_toBeEncryptedMove >> 8);
	//move[3] = (_toBeEncryptedMove >> 0);
	
	return decryptedMove;	
}

void Network::AskIfOkay(const PACKETTYPE _typeOfConfirmation)
{
	sf::Packet packetToSend;

	NetworkPacket data;
	data.packetType = PACKETTYPE::MESSAGE;
	data.moveData = 0;

	switch (_typeOfConfirmation)
	{
		case HOSTCOLOR:
		{	
			data.message = "IHOK";
			break;
		}
		case MOVE:
		{
			data.message = "IMOK";
			break;
		}
		case CONNECTION:
		{
			data.message = "RUOK";
			break;  
		}
		default:
			break;
	}

	//set data
	packetToSend << data;

	//send the packet to other player
	tcpSocket.send(packetToSend);
}

void Network::SendConfirmation(const PACKETTYPE _typeOfConfimation, const sf::Uint32 _move)
{
	sf::Packet packetToSend;

	NetworkPacket data;
	data.packetType = PACKETTYPE::CONFIRMATION;
	data.moveData = _move;

	switch (_typeOfConfimation)
	{		
		case HOSTCOLOR:
		{
			data.message = "HCOK";
		}
			break;
		case MOVE:
		{
			data.message = "MWOK";
		}
			break;
		case CONNECTION:
		{
			data.message = "IAOK";
		}
			break;
		default:
			break;
	}

	//fill our packet
	packetToSend << data;


	//send the packet to other player
	tcpSocket.send(packetToSend);
}

void Network::HandleReceivedPackets()
{
	/*for each (NetworkPacket packet in savedPackets)
	{
		switch (packet.packetType)
		{
		case HOSTCOLOR:
		{

		}
			break;
		case MOVE:
		{

		}
			break;
		case CONNECTION:
		{

		}
			break;
		case CONFIRMATION:
		{

		}
			break;
		case MESSAGE:
		{

		}
			break;
		default:
			break;
		}
	}*/
}