#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <iostream>



class Packet{
	public:
		uint64_t address;
        char command[32];
};


class db{
	public:
		int init(char* server,char* user,char* password, char* database);
		int isPacket(void);
		Packet recivePacket(void);
		void sendPacket(Packet);
	private:
		Packet packet;
		MYSQL* mysql;
		MYSQL_RES *res;
	        MYSQL_ROW row;
		char id[10];
		int selectQuery(void);
		int deleteQuery(char *id);
		Packet parsePacket(void);
};


int db::init(char* server,char* user,char* password, char* database){
	mysql = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(mysql, server, user, password, database, 0, NULL, 0)) {
		printf("%s\n", mysql_error(mysql));
		return 1;
    }else{
		printf("db connected\n");
		return 0;
    }
   return 2;

}
int db::isPacket(void){
	return selectQuery();
}
Packet db::recivePacket(void){
	packet = parsePacket();
	printf("packet recived\n");
	deleteQuery(id);
	printf("\n\n\n%i\n\n\n",packet.command[0]);

	return packet;
}
void db::sendPacket(Packet){}

int db::selectQuery(void){
	if (mysql_query(mysql,"SELECT * FROM commands_test ORDER BY priority;")){
        /*write error to log*/
        printf("%s\n", mysql_error(mysql));
	return 1;
    }
    if(!(this->res = mysql_store_result(mysql))){
        printf("%s\n", mysql_error(mysql));
	/*write error to log*/
        return 2;
    }
    if(!(row = mysql_fetch_row(res))){
	printf("%s\n", mysql_error(mysql));
	/*write error to log*/
	return 3;
    }
	printf("there is packet\n");

    return 0;
}

int db::deleteQuery(char *id){
	char query[100];
	memset (query,0,100);
	snprintf(query, 99, "DELETE FROM commands_test WHERE id = %s LIMIT 1;", id);
/*	if (mysql_query(mysql,query)){
        /*write error to log/
        return 1;
    }else{
		return 0;
	}*/
	return 0;
}
Packet db::parsePacket(void){
	int numFields = 0;
	char buf;
//	printf("1\n");

	packet.address = 0;
	memset(packet.command,0,31);
	memset(&buf,0,1);
//	printf("2\n");

	sscanf(row[0], "%s", id);
//	sscanf(this->row[3], "%llu", this->packet.address);
	//printf("\n");

	numFields = mysql_num_fields(res);
	printf("Fields %i\n",numFields);
	for (int i = 4 ; i < numFields; i++){
	//	printf("filling packets\n");
	//	printf("%s %d \n",row[i],row[i]);
		sscanf(row[i],"%u",&packet.command[i-4]);
//		printf("%u\n",packet.command[i-4]);
		}
//	printf("4\n");

	return packet;
}



int main(){
	db mysql;
	Packet testpacket;
	mysql.init("localhost","test","123","RCHome");
	int j = 0;
	while(1){
	memset(testpacket.command,0,32);
	if(!mysql.isPacket()){
			testpacket = mysql.recivePacket();
			printf("Result\n");

	for (int i = 0; i < 32; i++){
		printf("%i\n", testpacket.command[i]);
	}
	scanf("%i",&j);
	}

}


	return 0;
}



































