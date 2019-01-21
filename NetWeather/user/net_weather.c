/*
 * net_weather.c
 *
 * Created on: 20190121
 * Author: Litial Joeh
 */

#include "ets_sys.h"
#include "osapi.h"

void ICACHE_FLASH_ATTR user_esp_dns_found(const char *name, ip_addr_t *ipaddr,void *arg)
{
	weather_station_init(ipaddr);
}

void ICACHE_FLASH_ATTR getWeather(void)
{
	struct ip_addr addr;

	espconn_gethostbyname(&user_tcp_conn, URL_NET_WEATHER_HOST, &addr, user_esp_dns_found);
}

void ICACHE_FLASH_ATTR user_tcp_recv_cb(void *arg, char *pdata, unsigned short len)
{
	os_printf("\r\n -----Receiving data from Internet:----- \r\n ");
	uart0_tx_buffer(pdata, strlen(pdata));
}

void ICACHE_FLASH_ATTR user_tcp_sent_cb(void *arg)
{
	os_printf("\r\n -----Successfully----- \r\n ");
}

void ICACHE_FLASH_ATTR user_tcp_discon_cb(void *arg)
{
	os_printf("Disconnect OK\r\n ");
}

void ICACHE_FLASH_ATTR user_tcp_recon_cb(void *arg, sint8 err)
{
	os_printf("Connect Fail, Error Code: %d\r\n", err);
	espconn_connect((struct espconn *) arg);
}

void ICACHE_FLASH_ATTR user_tcp_connect_cb(void *arg)
{
	struct espconn *pespconn = arg;
	espconn_regist_recvcb(pespconn, user_tcp_recv_cb);
	espconn_regist_sentcb(pespconn, user_tcp_sent_cb);
	espconn_regist_disconcb(pespconn, user_tcp_discon_cb);

	os_printf("\r\n -----Send weather request----- \r\n");
	os_printf(PACKET_GET);

	espconn_sent(pespconn, PACKET_GET, strlen(PACKET_GET));
}

void ICACHE_FLASH_ATTR weather_station_init(struct ip_addr *remote_ip)
{
	//configuration
	user_tcp_conn.type = ESPCONN_TCP;
	user_tcp_conn.state = ESPCONN_NONE;
	user_tcp_conn.proto.tcp = (esp_tcp *) os_zalloc(sizeof(esp_tcp));

	os_memcpy(user_tcp_conn.proto.tcp->remote_ip, remote_ip, 4);
	//user_tcp_conn.proto.tcp->local_port = espconn_port();
	user_tcp_conn.proto.tcp->remote_port = 80;

	espconn_regist_connectcb(&user_tcp_conn, user_tcp_connect_cb);
	espconn_regist_reconcb(&user_tcp_conn, user_tcp_recon_cb);

	espconn_connect(&user_tcp_conn);
}
