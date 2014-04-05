CFLAGS =  -DBIG_JOINS=1  -fno-strict-aliasing  -g
LIBS = -L/usr/lib/arm-linux-gnueabihf -L./lib/librf24/ -lrf24 -lmysqlclient -lpthread -lz -lm -lrt -ldl
INCLUDE = -I/usr/include/mysql


ALL: mysql_db.o rchome.o
	g++ -Wall -o ./bin/prog $(INCLUDE) -DBIG_JOINS=1  -fno-strict-aliasing  -g -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s   main.cpp mysql_db.o rchome.o $(LIBS)

mysql_db.o: ./lib/mysql_db/mysql_db.cpp
	g++ -Wall -c $(INCLUDE) -DBIG_JOINS=1  -fno-strict-aliasing  -g ./lib/mysql_db/mysql_db.cpp -L/usr/lib/arm-linux-gnueabihf -lmysqlclient -lpthread -lz -lm -lrt -ldl

rchome.o: ./lib/rchome/rchome.cpp
	g++ -Wall -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -c -L./lib/librf24/  -lrf24 ./lib/rchome/rchome.cpp 
clean:
	rm *.o ./bin/prog
