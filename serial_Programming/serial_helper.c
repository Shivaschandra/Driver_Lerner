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
 * @file        serial_ext.cpp
 * @author      Krishnaraj
 * @brief       serial port interface function implementations
 */

#include <fcntl.h>
#include <asm/termios.h>

/* define ioctl(), its header clashes with asm/termios.h */
extern int ioctl(int, int, ...);

int serial_speed_set(int fd, int baud)
{
  struct termios2 tty;

  ioctl(fd, TCGETS2, &tty);
  tty.c_cflag &= ~CBAUD;
  tty.c_cflag |= BOTHER;
  tty.c_ispeed = baud;
  tty.c_ospeed = baud;

  return ioctl(fd, TCSETS2, &tty);
}

#if 0 /* legacy code with fixed set of speeds */
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int serial_speed_set(int fd, int baud)
{
  struct termios tty;
  speed_t tty_speed;

  memset(&tty, 0, sizeof(struct termios));
  if(tcgetattr(fd, &tty) != 0) return -1;

  switch(baud)
  {
    case 0:       tty_speed = B0;       break;
    case 50:      tty_speed = B50;      break;
    case 75:      tty_speed = B75;      break;
    case 110:     tty_speed = B110;     break;
    case 134:     tty_speed = B134;     break;
    case 150:     tty_speed = B150;     break;
    case 200:     tty_speed = B200;     break;
    case 300:     tty_speed = B300;     break;
    case 600:     tty_speed = B600;     break;
    case 1200:    tty_speed = B1200;    break;
    case 1800:    tty_speed = B1800;    break;
    case 2400:    tty_speed = B2400;    break;
    case 4800:    tty_speed = B4800;    break;
    case 9600:    tty_speed = B9600;    break;
    case 19200:   tty_speed = B19200;   break;
    case 38400:   tty_speed = B38400;   break;
    case 57600:   tty_speed = B57600;   break;
    case 115200:  tty_speed = B115200;  break;
    case 230400:  tty_speed = B230400;  break;
    case 460800:  tty_speed = B460800;  break;
    case 576000:  tty_speed = B576000;  break;
    case 921600:  tty_speed = B921600;  break;
    case 1000000: tty_speed = B1000000; break;
    case 1152000: tty_speed = B1152000; break;
    case 1500000: tty_speed = B1500000; break;
    case 2000000: tty_speed = B2000000; break;
    case 2500000: tty_speed = B2500000; break;
    case 3000000: tty_speed = B3000000; break;
    case 3500000: tty_speed = B3500000; break;
    case 4000000: tty_speed = B4000000; break;

    default: return -1;
  }

  cfsetospeed(&tty, tty_speed);
  cfsetispeed(&tty, tty_speed);

  return tcsetattr(fd, TCSANOW, &tty);
}
#endif

