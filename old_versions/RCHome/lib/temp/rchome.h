#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <syslog.h>
#include "../librf24/RF24.h"

#define COMMAND_LENGHT 23 
#define RESPONSE_TIMEOUT 20000

class RCHome{
public:

  RCHome();
  
  int setBase(uint64_t base);
  uint64_t getBase(void);
  
  int setControllerSAddress(int sAddress);
  int getControllerSAddress(void);
  
  int send(char* input, char* output);
  int listen(char* output);

private:
  RF24 radio;
  
  uint64_t baseAddr;
  uint64_t controllerSAddress;
  
  void setDestinationAddress(int sAddress);
};
