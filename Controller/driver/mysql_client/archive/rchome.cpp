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

	struct Packet{
		uint64_t address;
		char command[32];
	};

	struct Mysql_connect{
		char *server;
                char *user;
                char *password;
                char *database;
	};



   	MYSQL_RES *res;
   	MYSQL_ROW row;

	void init(char* server,char* user,char* password, char* database){
		Mysql_connect conn;
                conn.server = server;
                conn.user = user;
                conn.password = password;
                conn.database = database;
		connectMysql(conn);
	}

	MYSQL* connectMysql(Mysql_connect conn){
		MYSQL* mysql;
		/*Mysql_connect conn;
		conn.server = "localhost";
   		conn.user = "test";
   		conn.password = "123";
   		conn.database = "RCHome";*/
		mysql = mysql_init(NULL);
   		/* Connect to database */
   		if (!mysql_real_connect(mysql, conn.server, conn.user, conn.password, conn.database, 0, NULL, 0)) {
      			fprintf(stderr, "%s\n", mysql_error(mysql));
      		return NULL;
   		}else{
			return mysql;
		}
	}

	int sendQuery( char* query, MYSQL* mysql){
		printf("Query: %s\n", query);
		if (mysql_query(mysql,query)){
			/*write error to log*/
			return 1;
			}
		if (!(res = mysql_store_result(mysql))){
			/*write error to log*/
			return 2;
		}
		if(!(row = mysql_fetch_row(res))){
			/*write error to log*/
		mysql_free_result(res);
			return 3;
		}
		mysql_free_result(res);
		return 0;
	}

	int main(){
		char command[32];
		char id[10];
		char query[100] ;
		char* ptrQuery = &query[0];
		MYSQL* mysql = connectMysql();
		snprintf(query, 99,"SELECT * FROM commands_test ORDER BY priority;");
		sendQuery(ptrQuery,mysql);

		memset (command,0,32);
//		for (int i = 4; i < )
		sscanf(row[4],"%u",command);
		sscanf(row[0], "%s", id);


		for (int j = 0; j < 32; j++){
			printf("%c  %d  %u\n",command[j],command[j], command[j]);
        	}

		snprintf(query, 99, "DELETE FROM commands_test WHERE id = %s LIMIT 1;", id);
		int k = sendQuery(ptrQuery,mysql);
		printf("%u\n",k);
		return 0;
	}
