#ifndef PACKET_H
#define PACKET_H

#define COMMAND_LENGHT 23 
#define RESPONSE_TIMEOUT 20000
class Packet{
	public:
		int senderSAddress;
		int recieverSAddress;
		long long unsigned int baseAddress;
		char command;
		char result;
		char sensors[COMMAND_LENGHT];
}; 

#endif
