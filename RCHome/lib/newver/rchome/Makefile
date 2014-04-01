CFLAGS =  -DBIG_JOINS=1  -fno-strict-aliasing  -g
LIBS = -L/usr/lib/arm-linux-gnueabihf -L./librf24/ -lrf24 -lmysqlclient -lpthread -lz -lm -lrt -ldl


ALL: rchome.o
	g++ -Wall -o ./prog  -DBIG_JOINS=1  -fno-strict-aliasing  -g -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s   main.cpp rchome.o $(LIBS)

rchome.o: ./rchome/rchome.cpp
	g++ -Wall -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -c -L./librf24/  -lrf24 ./rchome/rchome.cpp 
clean:
	rm *.o ./prog
