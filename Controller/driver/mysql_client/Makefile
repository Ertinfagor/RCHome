CFLAGS = -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing  -g
LIBS = -L/usr/lib/arm-linux-gnueabihf -lmysqlclient -lpthread -lz -lm -lrt -ldl



ALL:
	g++ -Wall -o class $(CFLAGS) class.cpp $(LIBS)
Compile:
	g++ -Wall -o mysql $(CFLAGS) mysql_db.cpp main.cpp $(LIBS)

