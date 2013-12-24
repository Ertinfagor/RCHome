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
  byte *ptr;
  ptr = &command[0];
  if ( radio.available() )
    {
     
      bool done = false;
      while (!done)
      {
        done = radio.read( ptr, sizeof(byte[32]) );

	// Delay just a little bit to let the other unit
	// make the transition to receiver
	delay(20);
      }
      runCommand(ptr);
      Serial.println(ptr[3]);
      radio.write(ptr, sizeof(byte[32]));
    }

}
bool runCommand(byte *ptr)
{
  Serial.println(ptr[1]);
  Serial.println(ptr[2]);
  Serial.println(ptr[3]);
  switch (ptr[1])
  {
    case 0:
      break;
    case 1:
      if (ptr[3]== 0x00)
      {
        switchOnLight(ptr);
      }
      break;
    case 2:
      if (ptr[3]== 0x00)
      {
        switchOffLight(ptr);
      }
      break;
  }

}

byte readTemp(void){}
byte readHum(void){}
byte readLight(void){}
bool switchOnLight(byte* ptr)
{
  digitalWrite(led, HIGH);
  ptr[3] = 0xFF;
}
bool switchOffLight(byte* ptr){
  digitalWrite(led, LOW);
  ptr[3] = 0xFF;
}
