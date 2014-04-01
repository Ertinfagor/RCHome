#include "./rchome/rchome.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char inputm[32];
        char outputm[32];
 	
	memset(inputm,0,COMMAND_LENGHT);
        memset(outputm,0,COMMAND_LENGHT);
	
	char* input = inputm;
	char* output = outputm;

	RCHome *nrf = new RCHome();
	printf("init\n");

	while(1){
		memset(input,0,COMMAND_LENGHT);
		memset(output,0,COMMAND_LENGHT);

		input[0] = 2;
		usleep(1000);
		printf("Send\n");

		for (int i = 0; i < COMMAND_LENGHT; i++){
			printf("%u", input[i]);
		}
		printf("\n");

		nrf->send(input,output);
		printf("Output:\n");
		for (int i = 0; i < COMMAND_LENGHT; i++){
			printf("%u", output[i]);
			}
			printf("\n");
		}



	return 0;
}

