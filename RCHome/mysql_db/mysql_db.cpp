#include "mysql_db.h"


db::db(char* server,char* user,char* password, char* database){
	mysql = mysql_init(NULL);
     snprintf(workDB,99,"%s",database);
	openlog("RCHome",LOG_PID, LOG_DAEMON);
	/* Connect to database */
    if (!mysql_real_connect(mysql, server, user, password, database, 0, NULL, 0)) {
		syslog(LOG_EMERG,"Can`t connect to db, %s",mysql_error(mysql));
		throw (mysql_error(mysql));
    }
	syslog(LOG_INFO,"DB connected");

}

int db::isPacket(void){
	return selectQuery();
}

Packet db::recivePacket(void){
	Packet packet = parsePacket();
	deleteQuery(id);

	return packet;
}

int db::sendPacket(Packet inputPacket){
	char query[10000];
        char buf[10];
	memset (query,0,9999);
	snprintf(query, 9999, "CREATE TABLE IF NOT EXISTS  %s.%llu LIKE templ_SensorBoard;",workDB,inputPacket.address );
	if (mysql_real_query(mysql,query,sizeof(query))){
		syslog(LOG_EMERG,"Can`t create table, %s",mysql_error(mysql));
		return 1;
	}
 	memset (query,0,9999);
        snprintf(query, 9999, "INSERT INTO %s.%llu VALUES (DEFAULT, NOW(), %llu, 0 ",workDB,inputPacket.address,inputPacket.address );
	for (int i = 0 ; i < COMMAND_LENGHT; i++){
		snprintf(buf,9,"%u",inputPacket.command[i]);
		strcat(query, " ,");
		strcat(query, buf);
	}
	strcat(query,");");
	if (mysql_real_query(mysql,query, sizeof(query))){
		syslog(LOG_EMERG,"Can`t write to table, %s",mysql_error(mysql));
		return 2;
	}
	syslog(LOG_INFO,"Packet writed to DB");
	return 0;
}

int db::selectQuery(void){
    if (mysql_query(mysql,"SELECT * FROM commands ORDER BY priority;")){
	syslog(LOG_EMERG,"Can`t SELECT, %s",mysql_error(mysql));
	return 1;
    }
    if(!(res = mysql_store_result(mysql))){
        syslog(LOG_EMERG,"Can`t store results, %s",mysql_error(mysql));
        return 2;
    }
    if(!(row = mysql_fetch_row(res))){
	mysql_free_result(res);
	//syslog(LOG_EMERG,"Can`t fetch, %s",mysql_error(mysql));
	return 3;
   }
   syslog(LOG_INFO,"Packet recieved from DB");
   return 0;
}

int db::deleteQuery(char *id){
	char query[100];
	memset (query,0,100);
	snprintf(query, 99, "DELETE FROM commands WHERE id = %s LIMIT 1;", id);
	if (mysql_query(mysql,query)){
        syslog(LOG_EMERG,"Can`t DELETE, %s",mysql_error(mysql)); 
        return 1;
    	}
	return 0;
}

/*int db::insertQuery(char* query, char* table){




	}





}*/

Packet db::parsePacket(void){
	Packet packet;
	int numFields = 0;
	packet.address = 0;

	memset(packet.command,0,COMMAND_LENGHT);

	sscanf(row[0], "%s", id);
	sscanf(row[2], "%llu", &packet.address);
	numFields = mysql_num_fields(res) - 4;
	for (int i = 0 ; i < numFields; i++){
		sscanf(row[i+4],"%u",&packet.command[i]);
	}

	mysql_free_result(res);
	return packet;
}

