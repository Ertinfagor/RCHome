#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F001LL, 0xF0F0F0F002LL };
const byte shortAddr = 0x02;
int led = 13;
char switchStatus = 0;
char lampStatus = 0;
void setup(void)
{
  Serial.begin(57600);

  radio.begin();
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
  char command[32] ;
  char *ptr;
  ptr = &command[0];
  if ( radio.available() )
    {
     
      bool done = false;
      while (!done)
      {
        done = radio.read( ptr, sizeof(char[32]) );
        delay(20);
      }
      runCommand(ptr);
      Serial.println(ptr[12]);
      
      radio.stopListening();
      radio.write(ptr, sizeof(byte[32]));
      radio.startListening();
    }

}
void runCommand(char *ptr)
{
  Serial.println(ptr[10]);
  switch (ptr[10])
  {
    case 0:
      break;
    case 1:
    {
      if (ptr[12]== 0x00){
        switchLight(ptr);
      }
      break;
    }
  }

}
void readAllSensors(char* ptr){
  readTemp(ptr);
  readHum(ptr);
  readLum(ptr);
  readSwitch(ptr);
  readLamp(ptr);
  
}
void readTemp(char* ptr){
  ptr[12] = 0xFF;
  ptr[13] = 0x02;
}
void readHum(char* ptr){
  ptr[12] = 0xFF;
  ptr[14] = 0x03;
}
void readLum(char* ptr){
  ptr[12] = 0xFF;
  ptr[15] = 0xFF;

}

void readSwitch(char* ptr){
  ptr[12] = 0xFF;
  ptr[15] = switchStatus;

}

void readLamp(char* ptr){
  ptr[12] = 0xFF;
  ptr[15] = lampStatus;

}

void switchLight(char* ptr)
{
  lampStatus = ptr[16];
  if(lampStatus == 0xFF){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
  ptr[12] = 0xFF;
}

