#include "client.h"
#include "iconv.h"
#include "stdio.h"
#include "string.h"
#include "driver/uart.h"

//�ɹ����յ��������������ݺ���
void ICACHE_FLASH_ATTR user_tcp_recv_cb(void *arg, char *pdata,
		unsigned short len) {
	os_printf("\r\n ----- ��ʼ��������----- \r\n ");
	uart0_tx_buffer(pdata, strlen(pdata));
	os_printf("\r\n -----������������-----  \r\n ");

}

//�������ݵ��������ɹ��Ļص�����
void ICACHE_FLASH_ATTR user_tcp_sent_cb(void *arg) {
	os_printf("�������ݳɹ���\r\n ");
}

//�Ͽ��������ɹ��Ļص�����
void ICACHE_FLASH_ATTR user_tcp_discon_cb(void *arg) {
	os_printf("�Ͽ����ӳɹ���\r\n ");
}

//����ʧ�ܵĻص�������errΪ�������
void ICACHE_FLASH_ATTR user_tcp_recon_cb(void *arg, sint8 err) {
	os_printf("���Ӵ��󣬴������Ϊ%d\r\n", err);
	espconn_connect((struct espconn *) arg);
}

//�ɹ����ӵ��������Ļص�����
void ICACHE_FLASH_ATTR user_tcp_connect_cb(void *arg) {
	struct espconn *pespconn = arg;
	espconn_regist_recvcb(pespconn, user_tcp_recv_cb);
	espconn_regist_sentcb(pespconn, user_tcp_sent_cb);
	espconn_regist_disconcb(pespconn, user_tcp_discon_cb);

	os_printf("\r\n ----- �������ݿ�ʼ----- \r\n");
	uart0_tx_buffer(buffer, strlen(buffer));
	os_printf("\r\n -----�������ݽ���-----  \r\n");

	espconn_sent(pespconn, buffer, strlen(buffer));

}
void ICACHE_FLASH_ATTR my_station_init(struct ip_addr *remote_ip,
		struct ip_addr *local_ip, int remote_port) {
	//����
	user_tcp_conn.type = ESPCONN_TCP;
	user_tcp_conn.state = ESPCONN_NONE;
	user_tcp_conn.proto.tcp = (esp_tcp *) os_zalloc(sizeof(esp_tcp));
	os_memcpy(user_tcp_conn.proto.tcp->local_ip, local_ip, 4);
	os_memcpy(user_tcp_conn.proto.tcp->remote_ip, remote_ip, 4);
	user_tcp_conn.proto.tcp->local_port = espconn_port();
	user_tcp_conn.proto.tcp->remote_port = remote_port;
	//ע��
	espconn_regist_connectcb(&user_tcp_conn, user_tcp_connect_cb);
	espconn_regist_reconcb(&user_tcp_conn, user_tcp_recon_cb);
	//���ӷ�����
	espconn_connect(&user_tcp_conn);
}
