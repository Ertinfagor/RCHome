#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F001LL, 0xF0F0F0F002LL };
const byte shortAddr = 0x02;
int led = 13;
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
  
  // Testing switch on/off
   pinMode(led, OUTPUT);  
 
  
  
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
      runCommand(command[1],command[2]);
    }

}
bool runCommand(byte command, byte parameter)
{
  Serial.println(command);
  switch (command)
  {
    case 0:
      break;
    case 1:
      switchOnLight(parameter);
      break;
    case 2:
      switchOffLight(parameter);
      break;
  }

}
byte readTemp(void){}
byte readHum(void){}
byte readLight(void){}
bool switchOnLight(byte number){digitalWrite(led, HIGH);}
bool switchOffLight(byte number){digitalWrite(led, LOW);}
