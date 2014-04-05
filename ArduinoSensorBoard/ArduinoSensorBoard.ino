#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "DHT.h"
#include <EEPROM.h>

//#include "printf.h"

#define DHTPIN 2 
#define DHTTYPE DHT11 
#define ADDRBASE 0xF0F0F0F000LL

byte serialIncomingByte = 0;

byte sensorValues[32] = {};

int rwBytes[] = {
  10};
int rwPins[] = {
  3};


int isUpdate = 0;
int shortRCHomeAddr = 1;
int shortASBoardAddr = 2;
int lightsSnsorPin = A0;

RF24 radio(8,9);
DHT dht(DHTPIN, DHTTYPE);


void setup(void)
{
  Serial.begin(57600);

  dht.begin();
  radio.begin();
  radio.setAutoAck(true);
  radio.setRetries(15,15);
  radio.setPALevel(RF24_PA_MAX);
  
  EEPROM.write(1,shortASBoardAddr);
  EEPROM.write(2,shortRCHomeAddr);
  
  sensorValues[0]= EEPROM.read(1);
  
  radio.openReadingPipe(1,ADDRBASE + EEPROM.read(1));
  radio.openWritingPipe(ADDRBASE + EEPROM.read(2));
  
  radio.startListening();

  for(int i = 0; i < sizeof(rwBytes)-1; i++){
    pinMode(rwPins[i], OUTPUT);  
  }
for (int i = 0; i < 32; i++){sensorValues[i]=i;}

}

void loop(void)
{
  byte command[32] ;
  byte *ptr = &command[0];
  uint8_t pipenum = 0;
  
  readSensors();
  
  if (isUpdate){
      sendUpdate();
  }
  
  if (Serial.available() > 0) {  //если есть доступные данные
    // считываем байт
    serialIncomingByte = Serial.read();

    // отсылаем то, что получили
    Serial.println(serialIncomingByte);
    switch(serialIncomingByte){
    case 49: 
      Serial.println("EEEPROM:");
      for (int i=0;i<35;i++){
        Serial.print(EEPROM.read(i));
        Serial.print(" ");        
      }

      break;
    }
  }
  if ( radio.available(&pipenum))
  {

    bool done = false;
    while (!done)
    {
      done = radio.read( ptr, sizeof(byte[32]) );
      delay(10);
    }
    if (pipenum==1){
      Serial.println(ptr[1]);
      runCommand(ptr);
    }
  }
  


}

void sendUpdate(){
    isUpdate = 0;
    radio.stopListening();
    radio.write(sensorValues, sizeof(byte[32]));
    radio.startListening();
}




void runCommand(byte *ptr)
{
    if(!ptr[2]){
    sendUpdate();
  }
  else{
    for(int i = 0; i < sizeof(rwBytes)-1; i++){
       if (sensorValues[rwBytes[i]] != ptr[rwBytes[i]]){
           sensorValues[rwBytes[i]] = ptr[rwBytes[i]];
           writeSwitch(i); 
       }
  }
     sendUpdate();
  }

}








void readSensors(void){
  readTemp();
  readHum();
  readLum();
    
}


void readTemp(void){
  float t = dht.readTemperature();
  if ((!isnan(t)) && (t != sensorValues[4])){
    sensorValues[4] = (byte)t;
    isUpdate = 1;
    Serial.println("tupdate");
  }
  


}
void readHum(void){
  float h = dht.readHumidity();
  if ((!isnan(h)) && (h != sensorValues[5])){
      sensorValues[5] = (byte)h;  
      isUpdate = 1;
      Serial.println("hupdate");
  }
  
}
void readLum(void){
  int l = analogRead(lightsSnsorPin);
  if(l!=sensorValues[6]){
     sensorValues[6] = l;
     isUpdate = 1; 
     Serial.println("lupdate");
  } 

}


void writeSwitch(int i){
    digitalWrite(rwPins[i], sensorValues[rwBytes[i]]);
        
  
}




