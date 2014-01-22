#include "mysql_db.h"


int db::init(char* server,char* user,char* password, char* database){
	mysql = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(mysql, server, user, password, database, 0, NULL, 0)) {
		return 1;
    }

	return 0;
}

int db::isPacket(void){
	return selectQuery();
}

Packet db::recivePacket(void){
	packet = parsePacket();
	deleteQuery(id);

	return packet;
}

int db::sendPacket(Packet inputPacket){
	char query[10000];
        char buf[10];
	printf("write to table %llu\n", inputPacket.address);
	memset (query,0,9999);
	snprintf(query, 9999, "CREATE TABLE IF NOT EXISTS  RCHome.%llu LIKE templ_result;",inputPacket.address );
	if (mysql_real_query(mysql,query,sizeof(query))){
		printf("Can`t create table\n");
		return 1;
	}
 	memset (query,0,9999);
        snprintf(query, 9999, "INSERT INTO RCHome.%llu VALUES (%llu ,NOW() ",inputPacket.address,inputPacket.address );
	for (int i = 0 ; i < 32; i++){
		snprintf(buf,9,"%u",inputPacket.command[i]);
		strcat(query, " ,");
		strcat(query, buf);
	}
	strcat(query,");");
	if (mysql_real_query(mysql,query, sizeof(query))){
		printf("Can`t write to table\n");
		return 2;
	}
	return 0;
}

int db::selectQuery(void){
	if (mysql_query(mysql,"SELECT * FROM commands_test ORDER BY priority;")){

	return 1;
    }
    if(!(res = mysql_store_result(mysql))){
        /*write error to log*/
        return 2;
    }
    if(!(row = mysql_fetch_row(res))){
	/*write error to log*/
	return 3;
    }
    return 0;
}

int db::deleteQuery(char *id){
	char query[100];
	memset (query,0,100);
	snprintf(query, 99, "DELETE FROM commands_test WHERE id = %s LIMIT 1;", id);
	if (mysql_query(mysql,query)){
        /*write error to log*/
        return 1;
    	}
	return 0;
}

/*int db::insertQuery(char* query, char* table){




	}





}*/

Packet db::parsePacket(void){
	int numFields = 0;
	packet.address = 0;

	memset(packet.command,0,32);

	sscanf(row[0], "%s", id);
	sscanf(row[3], "%llu", &packet.address);
	numFields = mysql_num_fields(res) - 4;
	for (int i = 0 ; i < numFields; i++){
		sscanf(row[i+4],"%u",&packet.command[i]);
	}


	return packet;
}

