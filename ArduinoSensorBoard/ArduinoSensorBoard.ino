#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "DHT.h"
//#include "printf.h"

#define DHTPIN 2 
#define DHTTYPE DHT11 

RF24 radio(9,10);
DHT dht(DHTPIN, DHTTYPE);

const uint64_t pipes[2] = { 0xF0F0F0F001LL, 0xF0F0F0F002LL };
const byte shortAddr = 0x02;
int led = 13;
byte lampStatus = 0;
byte switchStatus = 0;

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
   pinMode(led, OUTPUT);  
 
  
  
}

void loop(void)
{
  byte command[32] ;
  byte *ptr = &command[0];
  uint8_t pipenum = 0;
  if ( radio.available(&pipenum))
    {
     
      bool done = false;
      while (!done)
      {
        done = radio.read( ptr, sizeof(byte[32]) );
        delay(10);
      }
      if (pipenum==1){
          runCommand(ptr);
      }
      Serial.println(ptr[13]);
      
      radio.stopListening();
      radio.write(ptr, sizeof(byte[32]));
      radio.startListening();
    }
    
  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'D'){
       Serial.println("Test message");
      //radio.printDetails();        //GOING TO ARDUINO DOWN
    }
    
  }
}
void runCommand(byte *ptr)
{
  Serial.println(ptr[10]);
  switch (ptr[10])
  {
    case 0:
    {
      readAllSensors(ptr);  
      break;
    }
    case 1:
    {
      if (ptr[12]== 0){
        switchLight(ptr);
      }
      break;
    }
  }

}
void readAllSensors(byte* ptr){
  readTemp(ptr);
  readHum(ptr);
  readLum(ptr);
  readSwitch(ptr);
  readLamp(ptr);
  
}
void readTemp(byte* ptr){
  float t = dht.readTemperature();
  if (!isnan(t)){
    ptr[13] = (byte)t;
    ptr[12] = 255;
  }else{
    ptr[12] = 13;      
  }
  
  
}
void readHum(byte* ptr){
  float h = dht.readHumidity();
  if (!isnan(h)){
    ptr[14] = (byte)h;
    ptr[12] = 255;
  }else{
    ptr[12] = 14;      
  }
}
void readLum(byte* ptr){
  ptr[12] = 255;
  ptr[15] = 14;

}

void readLamp(byte* ptr){
  ptr[12] = 255;
  ptr[16] = lampStatus;

}
void readSwitch(byte* ptr){
  ptr[12] = 255;
  ptr[17] = switchStatus;

}



void switchLight(byte* ptr)
{
  lampStatus = ptr[16];
  if(lampStatus == 255){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
  ptr[12] = 255;
}

