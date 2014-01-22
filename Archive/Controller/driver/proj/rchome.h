#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "../packet/packet.h"
#include "../librf24/RF24.h"

class RCHome{
public:
  
  RCHome();
  int init(void);
  Packet runCommand(Packet);
 
  
  
private:
  RF24 radio;
  Packet outputPacket;
  uint64_t controllerAddres;
  void setAddress(uint64_t parsedAddress);
  void sendCommand(char* input, char* output);
  
  
  
  
};
