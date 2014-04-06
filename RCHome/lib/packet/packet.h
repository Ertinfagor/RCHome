#ifndef PACKET_H
#define PACKET_H

#define COMMAND_LENGHT 23 
#define RESPONSE_TIMEOUT 20000
class Packet{
	public:
		long long unsigned int address;
        	char command[COMMAND_LENGHT];
		int error;
}; 

#endif
