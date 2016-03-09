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
 * @file        logger.h
 * @author      Krishnaraj
 * @brief       interfaces for logging
 */

#ifndef __LOGGER_H_
#define __LOGGER_H_

#define LOG_TAG     "AMS"

enum
{
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR
};

#if AMS_DEBUG_LOGS
#define LOGD(...) logger(LOG_DEBUG, __VA_ARGS__)
#else
#define LOGD(...)
#endif

#if AMS_INFO_LOGS
#define LOGI(...) logger(LOG_INFO, __VA_ARGS__)
#else
#define LOGI(...)
#endif

#define LOGW(...) logger(LOG_WARNING, __VA_ARGS__)
#define LOGE(...) logger(LOG_ERROR, __VA_ARGS__)

  /**
   * @brief       log function to report error
   * @param[in]   type kind of log
   * @param[in]   ... variable number of args as for printf
   * @return      void
   */
void logger(int type, const char *fmt, ...);

#endif // __LOGGER_H_
