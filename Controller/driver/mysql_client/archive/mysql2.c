/* Simple C program that connects to MySQL Database server*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <string.h>
	//#include <cstdlib>
	//#include <iostream>
	//#include "./librf24/RF24.h"
	#include <mysql.h>
	
	MYSQL* mysql;
   	MYSQL_RES *res;
   	MYSQL_ROW row;

	void exiterr(int exitcode){
  		fprintf(stderr, "%s\n", mysql_error(mysql));
	}





	int main() {
   		char *server = "localhost";
   		char *user = "test";
   		char *password = "123"; /* set me first */
   		char *database = "RCHome";
   		int i =0;
		char id[10];
		char query[100] ;


		mysql = mysql_init(NULL);
   		/* Connect to database */
   		if (!mysql_real_connect(mysql, server, user, password, database, 0, NULL, 0)) {
      			fprintf(stderr, "%s\n", mysql_error(mysql));
      		return 1;
   		}
   		/* send SQL query */


		while(1){
			if (mysql_query(mysql,"SELECT * FROM commands_test ORDER BY priority;")){
				/*write error to log*/
				continue;

			}
			if (!(res = mysql_store_result(mysql))){
				/*write error to log*/
                                continue;
			} 
			if(!(row = mysql_fetch_row(res))){
				/*write error to log*/
                                continue;
			}
			for (i=0 ; i < mysql_num_fields(res); i++){
				strcpy(id,  row[0]);
				printf("%s\n ",row[i]);
			}
				printf("\n");
			char command[32];
			memset (command,0,32);
			unsigned long long int address;
			printf("%s %c %llu %ll\n",row[3],row[3],row[3],row[3]);
			sscanf(row[3],"%llu",address);
			printf("Addres: %llu\n\n\n",address);
			sscanf(row[4],"%d",command);
			//strcpy(command,row[6]);
			//for(int k=0;k<32;k++) command[k]-='0';  /*workaround*/
			for (int j = 0; j < 32; j++){
			printf("%c  %d  %u\n",command[j],command[j], command[j]);
			}




			printf("\n");
int u = 0;
scanf("%i",&u);
			snprintf(query, 99, "DELETE FROM commands_test WHERE id= %s LIMIT 1;", id);
			if (mysql_real_query(mysql,&query,99)){

				/*write error to log*/
                                continue;
			}



/*
			if (!mysql_eof(res)){
				/*write error to log
                                continue;
			}
*/

}




   /* close connection */
   mysql_free_result(res);
   mysql_close(mysql);
}

