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

struct PacketData
{
	sf::Uint8 packetType; // the purpose is to identify what kind of an action we want to achieve
	sf::Uint8 confirmationData; // if we send confirmation - not necessary
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
			
	void SendMove(std::string move);


	PacketData* ListenForPackets(); // not done
	PacketData* HandleReceivedPackets(sf::Packet packet); // not done
	
	//used to confirm that other player has received vital information
	void AskIfOkay(const PACKETTYPE typeOfConfirmation); //done
	void SendConfirmation(const PACKETTYPE typeOfConfirmation, const sf::Uint32 move = 0); // done 
	void SendHostColor(const bool isWhite); //done
	void EncryptMove(); // not done
	std::string UnPackMove(sf::Int32 toBeDecryptedMove); //not done
	sf::Uint32 PackMove(const char move[]); // done
	
	void SetHostIP(const std::string hostIP);
	void SetPort(const unsigned short port);
	void SavePacket(PacketData* receivedPacket);

	void SetBlocking(bool isBlocking);

	sf::Packet PackPacket(PacketData data);
	PacketData* UnPackPacket(sf::Packet unpack);
	//data buffers

	unsigned short port;

	char dataBuffer[4096];

	char textBuffer[2048];
	sf::Uint32 moveBuffer;	
	
	std::size_t received;
	bool isHost = false;

	//std::map
	std::vector <PacketData*> savedPackets;

	std::string hostIP;
	sf::TcpListener listener;
	sf::TcpSocket tcpSocket;
};

inline sf::Packet& operator <<(sf::Packet& packet, const PacketData& networkPacket);
inline sf::Packet& operator >>(sf::Packet& packet, PacketData& networkPacket);

sf::Packet& operator <<(sf::Packet& packet, const PacketData& networkPacket)
{
	return packet << networkPacket.packetType << networkPacket.confirmationData  << networkPacket.moveData << networkPacket.message;
}

sf::Packet& operator >>(sf::Packet& packet, PacketData& networkPacket)
{
	return packet >> networkPacket.packetType >> networkPacket.confirmationData >> networkPacket.moveData >> networkPacket.message;
}
#endif
 