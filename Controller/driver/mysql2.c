/* Simple C program that connects to MySQL Database server*/
	#include <mysql.h>
	#include <stdio.h>
	#include <string.h>

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
			if (mysql_query(mysql,"SELECT * FROM commands ORDER BY priority;")){
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
				printf("%s ",row[i]);
			}
				printf("\n");
			char command[32];
			memset (command,'0',32);
			strcpy(command,row[2]);
			for(int k=0;k<32;k++) command[k]-='0';  /*workaround*/
			for (int j = 0; j < 32; j++){
			printf("%u\n",command[j]);
			}




			printf("\n");
int u = 0;
scanf("%i",&u);
			snprintf(query, 99, "DELETE FROM commands WHERE id= %s LIMIT 1;", id);
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

