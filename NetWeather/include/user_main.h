/*
 * user_main.h
 *
 *  Created on: 2015��7��16��
 *      Author: Administrator
 */

#ifndef APP_INCLUDE_USER_MAIN_H_
#define APP_INCLUDE_USER_MAIN_H_
#include "osapi.h"
#include "user_interface.h"
#include "client.h"
//#include "uart.h"

ETSTimer connect_timer;
ETSTimer station_check;

void Check_WifiState(void);

#endif /* APP_INCLUDE_USER_MAIN_H_ */
