#include "./rchome/rchome.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char inputm[32];
        char outputm[32];
 	
	
	char* input = inputm;
	char* output = outputm;

	RCHome *nrf = new RCHome();
	printf("init\n");

	while(1){
		memset(input,0,COMMAND_LENGHT);
		memset(output,0,COMMAND_LENGHT);

		input[0] = 2;
		//sleep(100);
		printf("Send\n");

		for (int i = 0; i < COMMAND_LENGHT; i++){
			printf("%d", input[i]);
		}
		printf("\n");

		nrf->send(input,output);
		printf("Output:\n");
		for (int i = 0; i < COMMAND_LENGHT; i++){
			printf("%d", output[i]);
			}
			printf("\n");
		}



	return 0;
}

