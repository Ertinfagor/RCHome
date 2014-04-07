#include "rchome.h"



RCHome::RCHome():radio("/dev/spidev0.0",8000000 , 25) {
	radio.begin();
	radio.setRetries(15,15);
	radio.setChannel(1);
	radio.setPALevel(RF24_PA_MAX);
	radio.setAutoAck(true);
	radio.startListening();
	openlog( "RCHome", LOG_PID, LOG_DAEMON);
}

int RCHome::setBase(uint64_t base){
	baseAddr = base;
	//correct check will be added
	return 0;
}

uint64_t RCHome::getBase(void){
return baseAddr;
}
  

int RCHOME::setControllerSAddress(int sAddress){
	controllerSAddress = sAddress;
	radio.stopListening();
	radio.openReadingPipe(1,baseAddr+sAddress);
	radio.startListening();
	//correct check will be added
	return 0;
}

int RCHOME::getControllerSAddress(void){
	return controllerSAddress;
}

void RCHOME::setDestinationAddress(int sAddress){
	radio.stopListening();
	radio.openWritingPipe(baseAddr+sAddress);
	radio.startListening();
}  

int RCHOME::send(char* input, char* output){
	memset(output,0,COMMAND_LENGHT);
	setDestinationAddress(input[0]);
	bool timeout = false;
	radio.stopListening();
	bool ok = radio.write( input, sizeof(char[COMMAND_LENGHT]) );
	if (!ok){
		__msleep(10);
		syslog(LOG_ERR, "Can`t send packet");
		return;
	}
	else{
		syslog(LOG_NOTICE, "Packet sended, wait for response...");
		radio.startListening();
		unsigned long started_waiting_at = __millis();
		while ( ! radio.available() && ! timeout ) {
			__msleep(5);
			if (__millis() - started_waiting_at > RESPONSE_TIMEOUT )
				{
					timeout = true;
				}
			}
	}

	if ( timeout ){
		syslog(LOG_ERR, "Timeout send packet");
		return;
	}
	else{
		radio.read( output, sizeof(char[COMMAND_LENGHT]) );
		syslog(LOG_NOTICE, "Packet recieved");
		return;
	}
}


int RCHOME::listen(char* output){
	memset(output,0,COMMAND_LENGHT);
	if (radio.available()){
		radio.read( output, sizeof(char[COMMAND_LENGHT]) );
		return 1;
	}
	return 0;
}
