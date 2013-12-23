#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F001LL, 0xF0F0F0F002LL };
 
void setup(void)
{
  Serial.begin(57600);

  radio.begin();
  //radio.setChannel(0x4b);
  radio.setAutoAck(false);
  radio.setRetries(15,15);
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(1,pipes[1]);
  radio.openWritingPipe(pipes[0]);
  
  radio.startListening();
}

void loop(void)
{
  byte command[32] ;
  if ( radio.available() )
    {
     
      bool done = false;
      while (!done)
      {
        done = radio.read( &command, sizeof(byte[32]) );

	// Delay just a little bit to let the other unit
	// make the transition to receiver
	delay(20);
      }
      runCommand(command[1]);
    }

}
bool runCommand(byte command){Serial.println(command);}
byte readTemp(void){}
byte readHum(void){}
byte readLight(void){}
bool switchOnLight(void){}
bool switchOffLight(void){}
