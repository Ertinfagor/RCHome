#ifndef PACKET_H
#define PACKET_H

class Packet{
	public:
		long long unsigned int address;
        uint command[32];
	int error;
}; 

#endif
