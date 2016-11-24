#ifndef NETWORK_H
#define NETWORK_H

class Network
{
public:
	void AskIfOkay();
	void Confirm(bool okay);
	void SendHostColor();
	char* Decrypt(__int32 toBeDecryptedMove);		
	__int32 PackMove(const char move[]);
	
private:



};

#endif

//PackMove
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

//Decrypt
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
