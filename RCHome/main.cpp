#include "./lib/mysql_db/mysql_db.h"
#include "./lib/rchome/rchome.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	db* conn = new db("localhost","test","123","RCHome1");
	RCHome *nrf = new RCHome();
	//conn.init("localhost","test","123","RCHome");
	Packet testpacket, test2packet;
	FILE *fp = NULL;
	fp = fopen("./log/output.log", "a+");
	fprintf(fp, "init\n");
	while(1){
		memset(testpacket.command,0,COMMAND_LENGHT);
		memset(test2packet.command,0,COMMAND_LENGHT);
		usleep(1000);
		if(!conn->isPacket()){
			testpacket = conn->recivePacket();

			fprintf(fp, "Send\n");
			for (int i = 0; i < COMMAND_LENGHT; i++){
				fprintf(fp, "%u", testpacket.command[i]);
			}
			fprintf(fp,"\n");

			test2packet = nrf->runCommand(testpacket);

			fprintf(fp, "Send\n");
			for (int i = 0; i < COMMAND_LENGHT; i++){
				fprintf(fp,"%u", test2packet.command[i]);
			}
			fprintf(fp,"\n");
			conn->sendPacket(test2packet);
		}

	}


	return 0;
}

