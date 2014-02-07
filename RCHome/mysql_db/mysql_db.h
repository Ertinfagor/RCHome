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
#include <syslog.h>
#include "../packet/packet.h"




class db{
        public:
                db(char* server,char* user,char* password, char* database);
		//int init(char* server,char* user,char* password, char* database);
                int isPacket(void);
                Packet recivePacket(void);
                int sendPacket(Packet inputPacket);
        private:
                Packet packet;
                MYSQL* mysql;
                MYSQL_RES *res;
                MYSQL_ROW row;
                char id[10];
                int selectQuery(void);
                int deleteQuery(char *id);
                int insertQuery(char* query, char* table);
                Packet parsePacket(void);
};


