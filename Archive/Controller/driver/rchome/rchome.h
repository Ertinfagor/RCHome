#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "../librf24/RF24.h"
#include "../packet/packet.h"


class RCHome{
public:
  int init(void);
  Packet runCommand(Packet);
  
  
private:
  RF24 radio;
  Packet outputPacket;
  uint64_t controllerAddres;
  void setAddress(uint64_t parsedAddress);
  void sendCommand(char* input, char* output);
  
  
  
  
};