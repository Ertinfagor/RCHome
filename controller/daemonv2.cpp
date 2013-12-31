#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "./librf24/RF24.h"

RF24 radio("/dev/spidev0.0",8000000 , 25);
const int role_pin = 7;
const uint64_t pipes[2] = { 0xF0F0F0F001LL, 0xF0F0F0F002LL };

void initRF24(void){
	radio.begin();
        radio.setRetries(15,15);
        radio.setChannel(1);
        radio.setPALevel(RF24_PA_MAX);
        radio.openWritingPipe(pipes[0]);
        radio.openReadingPipe(1,pipes[1]);
        radio.startListening();
}

int sendCommand(char* input, FILE* fp){
	bool timeout = false;

	radio.stopListening();
	bool ok = radio.write( input, sizeof(char[32]) );
	if (!ok){
        	input[12] = 1;
		__msleep(10);
		return 1;
	}
	else{
        	radio.startListening();
        	unsigned long started_waiting_at = __millis();
        	while ( ! radio.available() && ! timeout ) {
                	__msleep(5);
                	if (__millis() - started_waiting_at > 200 )
                	{
                        	timeout = true;
                	}
		}
        }

        if ( timeout )
        {

                input[12] = 2;
                return 2;


        }
        else
        {
                radio.read( input, sizeof(char[32]) );
                return 0;
        }

}


int main(int argc, char* argv[])
{
FILE *fp= NULL;
pid_t process_id = 0;
pid_t sid = 0;
// Create child process
process_id = fork();
// Indication of fork() failure
if (process_id < 0)
{
printf("fork failed!\n");
// Return failure in exit status
exit(1);
}
// PARENT PROCESS. Need to kill it.
if (process_id > 0)
{
printf("process_id of child process %d \n", process_id);
// return success in exit status
exit(0);
}
//unmask the file mode
umask(0);
//set new session
sid = setsid();
if(sid < 0)
{
// Return failure
exit(1);
}
// Change the current working directory to root.
chdir("/");
// Close stdin. stdout and stderr
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
// Open a log file in write mode.
fp = fopen ("Log.txt", "a+");
initRF24();
char input[32];
char * ptrInput = &input[0];
fputs("init\n",fp);
fflush(fp);
while (1)
{
//Dont block context switches, let the process sleep for some time
	sleep(1);
	if ( fgets (&input[0] , 32 , fp) != NULL ){
		sendCommand(&input[0], fp);
		fputs(input,fp);
		fflush(fp);
	}

}
fclose(fp);
return (0);
}

