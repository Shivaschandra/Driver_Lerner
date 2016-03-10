#include "serial.h"
#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 4){exit (0);}
  int i,n,nbytes,count = 0;
  char* port1 = argv[1];
  char* port2 = argv[2];
  uchar in_buffer[] = {'s','h','i','v','a'};
  uchar out_buffer[5],data_buff[5];
  int baudrate = atoi(argv[3]);

  printf("From:%s\n",port1);
  printf("To:%s\n",port2);
  printf("Baudrate:%d\n",baudrate);
  uart_t  serial_port1(port1,baudrate);
  uart_t  serial_port2(port2,baudrate);

  while(count < 1000)
  {
    serial_port1.push_tx(in_buffer,sizeof(in_buffer));
    for(i = 0; i < 5; i++)
      {
        serial_port2.read_rx(out_buffer+i,1);
        data_buff[i] = out_buffer[i];
        //printf("%c------%c",data_buff[i],out_buffer[i]);
      }
    //for(i=0;i<5;i++)
    //{
    //  printf("%c------%c",data_buff[i],out_buffer[i]);
    //}
    //nbytes = serial_port2.read_rx(out_buffer, 1);
    printf("Hi\n");
    n=memcmp ( in_buffer, data_buff, sizeof(in_buffer));

    if (n>0)
    {
      printf("Test failed at %d\n",count);
    }
    else
    {
      printf("Test passed at %d\n",count);
    }

    count ++;
  }
}
