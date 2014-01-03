#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
 printf ("init\n");

FILE *fp = NULL;
char input[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
fp = fopen ("log.txt", "a+");
while(1){
	if ( fread (&input[0], sizeof(char[32]) , 32 , fp) != 0 ){
		for(int i =0; i<32;i++){
			printf("%c",input[i]);
		}
		printf("\n");





// fwrite(input, sizeof(char[32]), 32 ,fp);
               //fflush(fp);
        }}


}
