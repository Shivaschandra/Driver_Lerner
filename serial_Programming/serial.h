

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
