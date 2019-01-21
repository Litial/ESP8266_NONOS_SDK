#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#include "osapi.h"
#include "user_interface.h"
#include "espconn.h"
#include "mem.h"

#define URL_NET_WEATHER_HOST	"api.seniverse.com"


#define PACKET_GET "GET /v3/weather/daily.json?key=rrpd2zmqkpwlsckt&location=yantai&language=en&unit=c&start=0&days=3 HTTP/1.1\r\nContent-Type: text/html;charset=utf-8\r\nAccept: */*\r\nHost: api.seniverse.com\r\nConnection: Keep-Alive\r\n\r\n"

struct espconn user_tcp_conn;

void getWeather(void);

void ICACHE_FLASH_ATTR weather_station_init(struct ip_addr *remote_ip);

#endif

