#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "../librf24/RF24.h"
#include "../packet/packet.h"


class RCHome{
public:
  int init(void);
  Packet runCommand(Packet);
  
  
private:
  RF24 radio;
  Packet outputPacket;
  const uint64_t controllerAddres;
  void setAddress(uint64_t parsedAddress);
  void sendCommand(char* input, char* output);
  
  
  
  
};

int RCHome::init(){
    
radio("/dev/spidev0.0",8000000 , 25);
const int role_pin = 7;
controllerAddres = 0xF0F0F0F001LL;
radio.begin();
radio.setRetries(15,15);
radio.setChannel(1);
radio.setPALevel(RF24_PA_MAX);
radio.startListening();  
  
  
  
  
}



void RCHome::setAddress(uint64_t parsedAddress){
	radio.stopListening();
	radio.openWritingPipe(parsedAddress);
	radio.openReadingPipe(1,controllerAddres);
	radio.startListening();
}



void RCHome::sendCommand(char* input, char* output){
	bool timeout = false;
	radio.stopListening();
	bool ok = radio.write( input, sizeof(char[32]) );
	if (!ok){
        	__msleep(10);
		outputPacket.error = 1;
		return;
	}
	else{
        	radio.startListening();
        	unsigned long started_waiting_at = __millis();
        	while ( ! radio.available() && ! timeout ) {
                	__msleep(5);
                	if (__millis() - started_waiting_at > 20000 )
                	{
                        	timeout = true;
                	}
		}
        }

        if ( timeout )
        {

                outputPacket.error = 2;
                return;


        }
        else
        {
                radio.read( output, sizeof(char[32]) );
                return;
        }

}

Packet RCHome::runCommand(Packet inputPacket){
  setAddress(inputPacket.address);
  sendCommand(inputPacket.command, outputPacket.command);
  outputPacket.address = inputPacket.address;
  
  return outputPacket;
  
  
  
}


int main(int argc, char* argv[])
{
return 0;
} 
