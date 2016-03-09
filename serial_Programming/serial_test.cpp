#include "serial.h"
#include "logger.h"
#include <stdio.h>
#include<stdlib.h>
using namespace std;
int main(int argc, char *argv[])
{
  if(argc < 4){exit (0);}
  char* port1 = argv[1];
  char* port2 = argv[2];
  int baudrate = atoi(argv[3]);
  printf("From:%s",port1);
  printf("To:%s",port2);
  printf("Baudrate:%d",baudrate);

}
