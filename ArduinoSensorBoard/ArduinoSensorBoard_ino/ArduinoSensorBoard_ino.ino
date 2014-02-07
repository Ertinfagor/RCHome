#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "DHT.h"
//#include "printf.h"

#define DHTPIN 2 
#define DHTTYPE DHT11 
#define COMMAND_LENGHT 23
RF24 radio(9,10);
DHT dht(DHTPIN, DHTTYPE);

const uint64_t pipes[2] = { 0xF0F0F0F001LL, 0xF0F0F0F002LL };
const byte shortAddr = 0x02;
int switchsPins[] = {13};
int switchesBytes[] = {13};
int switchStatus[] = {0};
void setup(void)
{
  Serial.begin(57600);
  
  dht.begin();
  radio.begin();
  
  radio.setAutoAck(false);
  radio.setRetries(15,15);
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(1,pipes[1]);
  radio.openWritingPipe(pipes[0]);
  
  radio.startListening();
  
  // Testing switch on/off
   pinMode(switchsPins[0], OUTPUT);  
 
  
  
}

void loop(void)
{
  byte command[COMMAND_LENGHT] ;
  byte *ptr = &command[0];
  uint8_t pipenum = 0;
  if ( radio.available(&pipenum))
    {
     
      bool done = false;
      while (!done)
      {
        done = radio.read( ptr, sizeof(byte[COMMAND_LENGHT]) );
        delay(10);
      }
      if (pipenum==1){
          runCommand(ptr);
      }
      Serial.println(ptr[1]);
      
      radio.stopListening();
      radio.write(ptr, sizeof(byte[COMMAND_LENGHT]));
      radio.startListening();
    }
    
  
}
void runCommand(byte *ptr)
{
  Serial.println(ptr[0]);
  if(!ptr[0]){
    readSensors(ptr);
  }else{
    writeSensors(ptr);
  }

}
void readSensors(byte* ptr){
  readTemp(ptr);
  readHum(ptr);
  readLum(ptr);
  readSwitch(ptr);
}

void writeSensors(byte* ptr){
  writeSwitch(ptr);
  readSwitch(ptr);
}

void readTemp(byte* ptr){
  float t = dht.readTemperature();
  if (!isnan(t)){
    ptr[2] = (byte)t;
    ptr[1] = 255;
  }else{
    ptr[1] = 13;      
  }
  
  
}
void readHum(byte* ptr){
  float h = dht.readHumidity();
  if (!isnan(h)){
    ptr[3] = (byte)h;
    ptr[1] = 255;
  }else{
    ptr[1] = 14;      
  }
}
void readLum(byte* ptr){
  ptr[4] = 255;
  ptr[1] = 255;

}

void readSwitch(byte* ptr){
  for(int i = 0; i < sizeof(switchesBytes); i++){
    ptr[switchesBytes[i]]=switchStatus[i];
  
  }
  ptr[1] = 255;
}

void writeSwitch(byte* ptr){
  for(int i = 0; i < sizeof(switchesBytes); i++){
    if(ptr[switchesBytes[i]]){
         digitalWrite(switchsPins[i], HIGH); 
    }else{
        digitalWrite(switchsPins[i], LOW);
    }
    switchStatus[i] = ptr[switchesBytes[i]];
    ptr[1] = 255;
  }
}


