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
const uint64_t controllerAddres = 0xF0F0F0F001LL;

void initRF24(void){
	radio.begin();
        radio.setRetries(15,15);
        radio.setChannel(1);
        radio.setPALevel(RF24_PA_MAX);
        radio.startListening();
}

void setAddress(uint64_t parsedAddress){
	radio.stopListening();
	radio.openWritingPipe(parsedAddress);
	radio.openReadingPipe(1,controllerAddres);
	radio.startListening();
}
uint64_t parseAddress(char* input){
	char sensorBoardAddress[10];
	uint64_t parsedAddress;
	for (int i = 0; i < 10; i++){
		sensorBoardAddress[i]=input[i];
	}
	parsedAddress = strtoull (sensorBoardAddress, NULL, 16);
	return parsedAddress;


}

int sendCommand(char* input, char* output){
	bool timeout = false;
	radio.stopListening();
	bool ok = radio.write( input, sizeof(char[32]) );
	if (!ok){
        	__msleep(10);
		output[12] = 1;
		return 1;
	}
	else{
        	radio.startListening();
        	unsigned long started_waiting_at = __millis();
        	while ( ! radio.available() && ! timeout ) {
                	__msleep(5);
                	if (__millis() - started_waiting_at > 20000 )
                	{
                        	timeout = true;
                	}
		}
        }

        if ( timeout )
        {

                output[12] = 2;
                return 2;


        }
        else
        {
                radio.read( output, sizeof(char[32]) );
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
fp = fopen ("log.txt", "a+");
initRF24();
char input[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char output[32]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char * ptrInput = &input[0];
char * ptrOutput = &output[0];
unsigned int num;
fputs("init\n",fp);
fflush(fp);

while (1)
{
	sleep(1);
	int i=0;
   	while(fscanf(fp, "%u ", &num) > 0) {
        	input[i] = num;
        	i++;
	}
	if ( i == 32 ){
		uint64_t reciverAddres;
		reciverAddres = parseAddress(ptrInput);
		setAddress(reciverAddres);
		int error = sendCommand(ptrInput, ptrOutput);
		if(!error){
	 		for(int i = 0; i < 32; i++){
              			fprintf(fp,"%u ",output[i]);
               		}
			fprintf(fp,"\n");
		}else{ fprintf(fp,"error %i\n",error);}
		fflush(fp);
	}
}
fclose(fp);
return (0);
}

