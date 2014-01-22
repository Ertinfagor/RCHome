CFLAGS =  -DBIG_JOINS=1  -fno-strict-aliasing  -g
LIBS = -L/usr/lib/arm-linux-gnueabihf -L../librf24/ -lrf24 -lmysqlclient -lpthread -lz -lm -lrt -ldl
INCLUDE = -I/usr/include/mysql


ALL: mysql_db.o rchome.o
	g++ -Wall -o prog $(INCLUDE) -DBIG_JOINS=1  -fno-strict-aliasing  -g -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s   main.cpp mysql_db.o rchome.o $(LIBS)

mysql_db.o: mysql_db.cpp
	g++ -Wall -c $(INCLUDE) -DBIG_JOINS=1  -fno-strict-aliasing  -g mysql_db.cpp -L/usr/lib/arm-linux-gnueabihf -lmysqlclient -lpthread -lz -lm -lrt -ldl

rchome.o: rchome.cpp
	g++ -Wall -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -c -L../librf24/  -lrf24 rchome.cpp 
clean:
	rm *.o prog
