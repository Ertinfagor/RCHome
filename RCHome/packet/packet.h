#ifndef PACKET_H
#define PACKET_H

class Packet{
	public:
		long long unsigned int address;
        char command[32];
	int error;
}; 

#endif
