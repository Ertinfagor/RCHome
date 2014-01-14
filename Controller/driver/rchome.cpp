#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>


	MYSQL* mysql;
   	MYSQL_RES *res;
   	MYSQL_ROW row;
	
	int connectMysql(){
		char *server = "localhost";
   		char *user = "test";
   		char *password = "123";
   		char *database = "RCHome";
		mysql = mysql_init(NULL);
   		/* Connect to database */
   		if (!mysql_real_connect(mysql, server, user, password, database, 0, NULL, 0)) {
      			fprintf(stderr, "%s\n", mysql_error(mysql));
      		return 1;
   		}else{
			return 0;
		}
	}
	
	int sendQuery(){
		if (mysql_query(mysql,"SELECT * FROM commands ORDER BY priority;")){
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
		
		connectMysql();
		
		
		
		memset (command,0,32);
		sscanf(row[4],"%d",command);
		
		for (int j = 0; j < 32; j++){
			printf("%c  %d  %u\n",command[j],command[j], command[j]);
        }

	
	
		return 0;
	}