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
	port = 52000;

	if (isHost)
	{	

		hostIP = sf::IpAddress::getLocalAddress().toString();
		listener.listen(port);

		std::cout << "waiting for other player to join the game" << std::endl;

		if (listener.accept(tcpSocket) == sf::Socket::Done)
		{
			std::cout << "client connected!" << std::endl;
		}
	}
	else
	{
		std::string serverIP;
		std::cout << "Give IP address to connect" << std::endl;

		std::cin >> serverIP;

		//serverIP = sf::IpAddress::getLocalAddress().toString();

		std::cout << "IP set to: " << serverIP << std::endl;

		SetHostIP(serverIP);
		
		//sf::Time connectionTimeoutTime = sf::seconds(4.0f);

		if (!tcpSocket.connect(serverIP, port)) //, connectionTimeoutTime))
		{
			//std::cout << "could not connect to the server!" << std::endl;

			//Initialize();
		}
	}
}

void Network::SendMove(std::string _move)
{
	PacketData data;
	data.packetType = PACKETTYPE::MOVE;
	data.confirmationData = 0;
	data.moveData = PackMove(_move.c_str());
	data.message = "";

	tcpSocket.send(PackPacket(data));
}

PacketData* Network::ListenForPackets()
{
	sf::Packet packet;

	//while (received <= 0)
	//{
		if (tcpSocket.receive(packet) == sf::Socket::Done)
		{
			std::cout << "message received!" << std::endl;

			return HandleReceivedPackets(packet);
		}
//	}

	return nullptr;
}

PacketData* Network::HandleReceivedPackets(sf::Packet _packet)
{
	std::cout << "handling package" << std::endl;

	PacketData* data = nullptr; // = new PacketData();
	data = UnPackPacket(_packet);

	switch (data->packetType)
	{
	case PACKETTYPE::HOSTCOLOR:
	{
		std::cout << "packet type: HOSTCOLOR " << std::endl;
		std::cout << "Confirmation data: " << data->confirmationData << std::endl;
		std::cout << "Packet type: " << data->packetType << std::endl;
		std::cout << "Move data: " << data->moveData << std::endl;
		std::cout << "Message: " << data->message << std::endl;
		break;
	}
	case PACKETTYPE::MOVE:
	{


		std::cout << "packet type: MOVE " << std::endl;
		std::cout << "Confirmation data: " << data->confirmationData << std::endl;
		std::cout << "Packet type: " << data->packetType << std::endl;
		std::cout << "Move data: " << data->moveData << std::endl;
		std::cout << "Message: " << data->message << std::endl;
		break;
	}
	case PACKETTYPE::CONNECTION:
	{
		std::cout << "packet type: CONNECTION " << std::endl;
		std::cout << "Confirmation data: " << data->confirmationData << std::endl;
		std::cout << "Packet type: " << data->packetType << std::endl;
		std::cout << "Move data: " << data->moveData << std::endl;
		std::cout << "Message: " << data->message << std::endl;
		break;
	}
	case PACKETTYPE::CONNECTED:
	{
		std::cout << "packet type: CONNECTED " << std::endl;
		std::cout << "Confirmation data: " << data->confirmationData << std::endl;
		std::cout << "Packet type: " << data->packetType << std::endl;
		std::cout << "Move data: " << data->moveData << std::endl;
		std::cout << "Message: " << data->message << std::endl;
		break;
	}
	case PACKETTYPE::CONFIRMATION:
	{
		std::cout << "packet type: CONFIRMATION " << std::endl;
		std::cout << "Confirmation data: " << data->confirmationData << std::endl;
		std::cout << "Packet type: " << data->packetType << std::endl;
		std::cout << "Move data: " << data->moveData << std::endl;
		std::cout << "Message: " << data->message << std::endl;
		break;
	}
	case PACKETTYPE::MESSAGE:
	{
		std::cout << "packet type: MESSAGE " << std::endl;
		std::cout << "Confirmation data: " << data->confirmationData << std::endl;
		std::cout << "Packet type: " << data->packetType << std::endl;
		std::cout << "Move data: " << data->moveData << std::endl;
		std::cout << "Message: " << data->message << std::endl;
		break;
	}
	default:
		break;
	}

	return data;
}

void Network::AskIfOkay(const PACKETTYPE _typeOfConfirmation)
{
	PacketData data;
	data.packetType = PACKETTYPE::MESSAGE;
	data.confirmationData = 0;
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

	tcpSocket.send(PackPacket(data));
}

void Network::SendConfirmation(const PACKETTYPE _typeOfConfimation, const sf::Uint32 _move)
{
	PacketData data;
	data.packetType = PACKETTYPE::CONFIRMATION;
	data.confirmationData = 0;
	data.moveData = _move;

	switch (_typeOfConfimation)
	{
	case PACKETTYPE::HOSTCOLOR:
	{
		data.message = "HCOK";
	}
		break;
	case PACKETTYPE::MOVE:
	{
		data.message = "MWOK";
	}
		break;
	case PACKETTYPE::CONNECTION:
	{
		data.message = "IAOK";
	}
	case PACKETTYPE::CONNECTED:
	{
		data.message = "IACD";
	}
		break;
	default:
		break;
	}

	tcpSocket.send(PackPacket(data));
}

void Network::SendHostColor(const bool _isWhite)
{
	sf::Packet packetToSend;

	PacketData data;
	data.packetType = PACKETTYPE::HOSTCOLOR;
	data.confirmationData = 0;
	data.moveData = 0;

	if (_isWhite)
	{
		data.message = "isWhite";
	}
	else
	{
		data.message = "notWhite";
	}

	std::cout << "sent color: " << data.message << std::endl;

	tcpSocket.send(PackPacket(data));
}

//NOT DONE
void Network::EncryptMove()
{

}

std::string UnPackMove(sf::Int32 _toBeDecryptedMove)
{
	_toBeDecryptedMove = ~_toBeDecryptedMove;

	char move[4];

	move[0] = (_toBeDecryptedMove >> 24);
	move[1] = (_toBeDecryptedMove >> 16);
	move[2] = (_toBeDecryptedMove >> 8);
	move[3] = (_toBeDecryptedMove >> 0);

	std::string unpackedMove = "";
	unpackedMove.append(move);

	/*unpackedMove = (_toBeDecryptedMove >> 24);
	unpackedMove = (_toBeDecryptedMove >> 16);
	unpackedMove = (_toBeDecryptedMove >> 8);
	unpackedMove = (_toBeDecryptedMove >> 0);*/

	return unpackedMove;
}

sf::Uint32 Network::PackMove(const char _move[])
{
	char revertedMove[4];

	for (size_t i = 0; i < 4; i++)
	{
		switch (_move[i])
		{
		case 'A':
		{
			revertedMove[i] = 'H';
			break;
		}
		case 'B':
		{
			revertedMove[i] = 'G';
			break;
		}
		case 'C':
		{
			revertedMove[i] = 'F';
			break;
		}
		case 'D':
		{
			revertedMove[i] = 'E';
			break;
		}
		case 'E':
		{
			revertedMove[i] = 'D';
			break;
		}
		case 'F':
		{
			revertedMove[i] = 'C';
			break;
		}
		case 'G':
		{
			revertedMove[i] = 'B';
			break;
		}
		case 'H':
		{
			revertedMove[i] = 'A';
			break;
		}
		case '1':
		{
			revertedMove[i] = '8';
			break;
		}
		case '2':
		{
			revertedMove[i] = '7';
			break;
		}
		case '3':
		{
			revertedMove[i] = '6';
			break;
		}
		case '4':
		{
			revertedMove[i] = '5';
			break;
		}
		case '5':
		{
			revertedMove[i] = '4';
			break;
		}
		case '6':
		{
			revertedMove[i] = '3';
			break;
		}
		case '7':
		{
			revertedMove[i] = '2';
			break;
		}
		case '8':
		{
			revertedMove[i] = '1';
			break;
		}

		default:
			break;
		}
	}

	//turn char formatted move into an integer
	sf::Uint32 packedMove = 0;
	packedMove = (revertedMove[0] << 24) + (revertedMove[1] << 16) + (revertedMove[2] << 8) + (revertedMove[3]);

	return packedMove;
}

void Network::SetHostIP(const std::string _hostIP)
{
	hostIP = _hostIP;
} 

void Network::SetPort(const unsigned short _port)
{
	port = _port;
}

void Network::SavePacket(PacketData* _receivedPacket)
{
	savedPackets.push_back(_receivedPacket);
}

void Network::SetBlocking(bool _isBlocking)
{
	tcpSocket.setBlocking(_isBlocking);
}

sf::Packet Network::PackPacket(PacketData _data)
{
	sf::Packet packet;

	packet << _data.packetType << _data.confirmationData << _data.moveData << _data.message;

	return packet;
}

PacketData* Network::UnPackPacket(sf::Packet _unpack)
{
	PacketData* data = new PacketData();

	_unpack >> data->packetType >> data->confirmationData >> data->moveData >> data->message;

	return data;
}

