/**********************************************************************************************
 * ATONARP MICRO SYSTEMS CONFIDENTIAL
 * Unpublished Copyright (c) 2015-2016 ATONARP, All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of ATONARP.
 * The intellectual and technical concepts contained herein are proprietary to ATONARP
 * and may be covered by U.S. and Foreign Patents, patents in process, and are protected
 * by trade secret or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written permission is obtained
 * from ATONARP. Access to the source code contained herein is hereby forbidden to
 * anyone except current ATONARP employees, managers or contractors who have executed
 * Confidentiality and Non-disclosure agreements explicitly covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or
 * disclosure of this source code, which includes information that is confidential
 * and/or proprietary, and is a trade secret, of ATONARP.
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY
 * OF OR THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF ATONARP
 * IS STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES.
 * THE RECEIPT OR POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY
 * OR IMPLY ANY RIGHTS TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE,
 * USE, OR SELL ANYTHING THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 **********************************************************************************************/

/**
 * @file        serial.cpp
 * @author      Krishnaraj
 * @brief       serial port interface function implementations
 */

#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "serial.h"

#define UART_DEBUG 1

#if UART_DEBUG
#include <stdio.h>
#endif


uart_t::uart_t(const char *device, int baudrate)
            : tty_fd(0), error(NO_ERROR)
{
  struct termios tty;
  int ret;

  tty_fd = open(device, (O_RDWR | O_NOCTTY | O_SYNC));
  if (tty_fd < 0)
  {
    error = INIT_FAIL;
    return;
  }

  if((ret = serial_speed_set(tty_fd, baudrate)) != 0)
  {
    error = INIT_FAIL;
    return;
  }

  memset(&tty, 0, sizeof(struct termios));
  if(tcgetattr (tty_fd, &tty) != 0)
  {
    error = INIT_FAIL;
    return;
  }

  tty.c_lflag = 0;                               // no signaling chars, no echo,
  tty.c_oflag = 0;                               // no remapping, no delays
  tty.c_cflag |= 0;                              // no parity
  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;    // 8-bit chars
  tty.c_iflag &= ~IGNBRK;                        // disable break processing
  tty.c_iflag &= ~(IXON | IXOFF | IXANY);        // disable xon/xoff s/w flow control
  tty.c_cflag |= (CLOCAL | CREAD);               // ignore modem controls,
  tty.c_cflag &= ~(PARENB | PARODD);             // enable reading, shut off parity
  tty.c_cflag &= ~CSTOPB;                        // use 1 stop bit, instead of 2
  tty.c_cflag &= ~CRTSCTS;                       // disable hw flowcontrol

  tty.c_iflag &= ~(ICRNL | INLCR);
  tty.c_oflag &= ~(OCRNL | ONLCR | OPOST);
  tty.c_oflag &= ~(CR1 | CR2 | CR3);
  tty.c_oflag |= (CR0 | ONOCR | ONLRET);
  tty.c_lflag &= ~(ICANON);                     /* disable canonical reading */

  if(tcsetattr(tty_fd, TCSANOW, &tty) != 0)
  {
    error = INIT_FAIL;
    return;
  }

  if(flush_io_buffers() != 0)
    error = INIT_FAIL;

  /* set to blocking on init */
  if(set_blocking() != 0)
    error = INIT_FAIL;
}

uart_t::~uart_t()
{
  if(tty_fd) close(tty_fd);
  tty_fd = 0;
}

int uart_t::push_tx(uchar *in_buffer, int len)
{
#if UART_DEBUG
  printf("uart <-- ");
  for(int i=0; i<len; i++)
  {
    if((in_buffer[i] >= 32) && (in_buffer[i] <= 127))
      printf("%c", in_buffer[i]);
    else
      printf("%02X", in_buffer[i]);
  }
  printf("\n");
#endif

  return write(tty_fd, in_buffer, len);
}

int uart_t::read_rx(uchar *out_buffer, int max_len)
{

  int len = read(tty_fd, out_buffer, max_len);
  

#if UART_DEBUG
  printf("uart --> ");
  for(int i=0; i<len; i++)
  {
    if((out_buffer[i] >= 32) && (out_buffer[i] <= 127))
      printf("%c", out_buffer[i]);
    else
      printf("%02X", out_buffer[i]);
  }
  printf("\n");
#endif

  return len;
}

int uart_t::set_blocking()
{
  struct termios tty;

  memset(&tty, 0, sizeof(struct termios));
  if(tcgetattr(tty_fd, &tty) != 0)
    return -1;

  /* set to blocking read until atleast 1 byte is received */
  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 0; /* no timeout */

  if(tcsetattr(tty_fd, TCSANOW, &tty) != 0)
    return -1;

  return 0;
}

int uart_t::set_nonblocking(int timeout)
{
  struct termios tty;

  memset(&tty, 0, sizeof(struct termios));
  if(tcgetattr(tty_fd, &tty) != 0)
    return -1;

  /* set to non-blocking read */
  tty.c_cc[VMIN] = 0;
  /* timeout ard is in msecs, convert it to 0.1 secs */
  tty.c_cc[VTIME] = (timeout / 100);

  if(tcsetattr(tty_fd, TCSANOW, &tty) != 0)
    return -1;

  return 0;
}

int uart_t::flush_io_buffers()
{
  uchar buf[16];
  int nbytes;

  /* flush any pending operations */
  tcflush(tty_fd, TCIOFLUSH);

  set_nonblocking(0);

  /* clear rx, so that we don't read junk */
  do
  {
    nbytes = read(tty_fd, buf, 16);
  } while(nbytes > 0);

  return set_blocking();
}
