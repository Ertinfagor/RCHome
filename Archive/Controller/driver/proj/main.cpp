#include "mysql_db.h"
#include "rchome.h"
#include <unistd.h>

int main(){
	db conn;
	RCHome *nrf = new RCHome();
	conn.init("localhost","test","123","RCHome");
	Packet testpacket, test2packet;

	while(1){
		memset(testpacket.command,0,32);
		memset(test2packet.command,0,32);
		sleep(1);
		if(!conn.isPacket()){
			testpacket = conn.recivePacket();
			printf("Result\n");
			for (int i = 0; i < 32; i++){
				printf("%i\n", testpacket.command[i]);
			}
			printf("end packet\n");
			
			test2packet = nrf->runCommand(testpacket);
			
			printf("Result2\n");
			for (int i = 0; i < 32; i++){
				printf("%i\n", test2packet.command[i]);
			}
			printf("end packet\n");
			
			conn.sendPacket(test2packet);
		}

	}	




	return 0;
}
