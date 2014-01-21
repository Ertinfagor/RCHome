#include "mysql_db.h"
#include <unistd.h>

int main(){
	db conn;
	conn.init("localhost","test","123","RCHome");
	Packet testpacket;

	while(1){
		memset(testpacket.command,0,32);
		sleep(1);
		if(!conn.isPacket()){
			testpacket = conn.recivePacket();
			printf("Result\n");

			for (int i = 0; i < 32; i++){
				printf("%i\n", testpacket.command[i]);
				testpacket.command[i]=i;
			}
			printf("end packet\n");
			conn.sendPacket(testpacket);
		}

	}	




	return 0;
}
