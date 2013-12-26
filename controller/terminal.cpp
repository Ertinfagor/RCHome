#include <cstdlib>
#include <iostream>

#include "../RF24/librf24-rpi/librf24/RF24.h"

RF24 radio("/dev/spidev0.0",8000000 , 25); 
const int role_pin = 7;
const uint64_t pipes[2] = { 0xF0F0F0F001LL, 0xF0F0F0F002LL };
void setup(void)
{
	radio.begin();
	radio.setRetries(15,15);
	radio.setChannel(1);
	radio.setPALevel(RF24_PA_MAX);
	radio.openWritingPipe(pipes[0]);
	radio.openReadingPipe(1,pipes[1]);
	radio.startListening();
	radio.printDetails();
}
void loop(char i)
{
	 radio.stopListening();
char send[4] = {0x1,i,0,0};
bool ok = radio.write( &send, sizeof(int[32]) );
 if (ok)
      printf("ok\n\r");
    else
      printf("failed.\n\r");
 radio.startListening();

    unsigned long started_waiting_at = __millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout ) {
     __msleep(5);
   if (__millis() - started_waiting_at > 200 )
	{
      timeout = true;
	}
    }

 if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      char recieve[32]; 
      radio.read( &recieve, sizeof(char[32]) );
      printf("%x\r\n",recieve[3]);
    }



}
int main(int argc, char** argv)
{
        char i;
	setup();
        while(1)
		{
		scanf("%x", &i);
		loop(i);
		}
        return 0;
}

