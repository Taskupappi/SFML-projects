#ifndef CHESSNETWORK_H
#define CHESSNETWORK_H

#include "SFML\Network.hpp"

/*
* Network commands:
* QUESTION
* IHOK = Is Host (Color) Okay? - this is used when we ask if player got host's color
* IMOK = Is Move Okay? - this is used when we check if the move was okay
* RUOK = Are You Okay? - this is for checking if the connection is still up
*
*CONFIRMATIONS
* IAOK = I Am Okay - used to tell the server/client the connection is still up
* HCOK = Host Color Okay - used to confirm the host's color has been received
* MWOK = Move Was Okay - move that was sent was okay
* 
*
*/

enum PACKETTYPE
{
	HOSTCOLOR,
	MOVE,
	CONNECTION,
	CONNECTED,
	CONFIRMATION,
	MESSAGE,
};

struct NetworkPacket
{
	sf::Uint8 packetType; // the purpose is to identify what kind of an action we want to achieve
	sf::Uint8 confirmationData; // if we send confirmation 
	sf::Uint32 moveData; //
	std::string message;
};

class Network
{
public:
	Network(const bool isHost);
	~Network();

	void Initialize(); // done

	//void HandlePackage(); - what is the purpose for this?
	void ListenForPackets(); // not done
	void HandleReceivedPackets(sf::Packet packet); // not done
	
	//used to confirm that other player has received vital information
	void AskIfOkay(const PACKETTYPE typeOfConfirmation); //done
	void SendConfirmation(const PACKETTYPE typeOfConfirmation, const sf::Uint32 move = 0); // done 
	void SendHostColor(const bool isWhite); //done
	void Encrypt(); // not done
	std::string Decrypt(sf::Int32 toBeDecryptedMove); //not done
	sf::Uint32 PackMove(const char move[]); // done
	
	void setHostIP(const std::string hostIP); // done
	void setPort(const unsigned short port); // done
	void SavePacket(const NetworkPacket receivedPackage); //done

	sf::Packet PackPacket(NetworkPacket packet); //pack the packet ready for sending
	NetworkPacket UnPackPacket(sf::Packet packet);

private:
	sf::IpAddress hostIP;
	unsigned short port;
	sf::TcpSocket tcpSocket;
	sf::TcpListener listener;

	//data buffers

	char dataBuffer[4096];

	char textBuffer[2048];
	sf::Uint32 moveBuffer;	
	
	std::size_t received;
	bool isHost = false;

	//std::map
	std::vector <NetworkPacket> savedPackets;
};

inline sf::Packet& operator <<(sf::Packet& packet, const NetworkPacket& networkPacket);
inline sf::Packet& operator >>(sf::Packet& packet, NetworkPacket& networkPacket);

sf::Packet& operator <<(sf::Packet& packet, const NetworkPacket& networkPacket)
{
	return packet << networkPacket.packetType << networkPacket.confirmationData  << networkPacket.moveData << networkPacket.message;
}

sf::Packet& operator >>(sf::Packet& packet, NetworkPacket& networkPacket)
{
	return packet >> networkPacket.packetType >> networkPacket.confirmationData >> networkPacket.moveData >> networkPacket.message;
}
#endif
 