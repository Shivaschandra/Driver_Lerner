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
 * @file        serial.h
 * @author      Krishnaraj
 * @brief       serial port interface functions
 */

#ifndef __SERIAL_H_
#define __SERIAL_H_
#include "common.h"

class uart_t
{
private:
  int tty_fd;

public:
  enum
  {
    NO_ERROR  = 0,
    INIT_FAIL = -1,
  } error;

  uart_t(const char *device, int baudrate);
  ~uart_t();

  /**
   * @brief       set the reading mode to blocking until 1 byte is received
   * @return      number of bytes pushed to uart on success, else -ve number
   */
  int set_blocking();

  /**
   * @brief       set the reading mode to non-blocking mode until timeout
   * @param[in]   timeout timeour in msecs. Minimum of 100 ms, otherwise will be set to 0
   * @return      number of bytes pushed to uart on success, else -ve number
   */
  int set_nonblocking(int timeout);

  /**
   * @brief       pushes buffer to uart tx
   * @param[in]   in_buffer character buffer
   * @param[in]   len number of bytes to push from buffer
   * @return      number of bytes pushed to uart on success, else -ve number
   */
  int push_tx(uchar *in_buffer, int len);

  /**
   * @brief       read atleast 1 byte from uart rx. Blocks until atlast
   *              one byte has arrived at rx
   * @param[out]  out_buffer byte buffer to write to
   * @param[in]   max_len number of maximum bytes to read
   * @return      actual number of bytes read on success, else -ve number
   */
  int read_rx(uchar *out_buffer, int max_len);

  /**
   * @brief       flush input, output buffers
   * @return      0 if successful; non-zero otherwise
   */
  int flush_io_buffers();
};


/**
 * @brief       sets the uart to required baudrate
 * @param[in]   fd fd of opened serial port
 * @param[in]   baudrate intended speed
 * @return      number of bytes pushed to uart on success, else -ve number
 */
#ifdef __cplusplus
 extern "C" {
#endif

int serial_speed_set(int fd, int baudrate);

#ifdef __cplusplus
 }
#endif

#endif // __SERIAL_H_
