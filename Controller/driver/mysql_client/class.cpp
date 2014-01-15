class Packet{
	public:
		uint64_t address;
        char command[32];
}


class db{
	public:
		int init(char* server,char* user,char* password, char* database);
		int isPacket(void);
		Packet recivePacket(void);
		void SendPacket(Packet);
	private:
		Packet packet;
		MYSQL* mysql;
		MYSQL_RES *res;
        MYSQL_ROW row;
		char id[10];
		int selectQuery(void);
		int deleteQuery(char *id);
		Packet parsePacket(void);
}


int db::init(char* server,char* user,char* password, char* database){
	this.mysql = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(this.mysql, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(mysql));
		return 1;
    }else{
		return 0;
    }

}
int db::isPacket(void){
	return selectQuery();
}
Packet db::recivePacket(void){
	this.packet = parsePacket();
	deleteQuery(id);
	return this.packet;
}
void db::SendPacket(Packet);

int db::selectQuery(void){
	if (mysql_query(mysql,"SELECT * FROM commands_test ORDER BY priority;"))){
        /*write error to log*/
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
	if (mysql_query(mysql,query))){
        /*write error to log*/
        return 1;
    }else{
		return 0;
	}
}
Packet parsePacket(void){
	int numFields = 0;
	this.packet.address = 0;
	memset(this.packet.command,0,32);
	
	sscanf(row[0], "%s", id);
	sscanf(row[3], "%llu", id);
	numFields = mysql_num_fields(res) - 4;
	for (i=4 ; i < numFields; i++){
		sscanf(row[i],"%u",this.packet.command[i-4]);
	}
}



int main(){
	db mysql;
	Packet testpacket;
	mysql.init("localhost","test","123","RCHome");
	int j = 0;
	while(1){
		if(mysql.isPacket()){
			testpacket = mysql.reciveQuery();
		}
	
	for (int i = 0; i < 32; i++){
		printf("%d\n", testpacket.command);
	}
	scanf("%i",j);
	
}


	return 0;
}



































