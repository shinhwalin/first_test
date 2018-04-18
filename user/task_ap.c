/*
 * ESPRSSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "esp_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lwip/lwip/sockets.h"
#include "para.h"
#include "webserver.h"

#define TCP_LOCAL_PORT 5188
#define TCP_DATA_LEN 4096
static unsigned char tcp_msg[TCP_DATA_LEN];
void wifi_handle_event_cb(System_Event_t *evt)
{
	//printf("event %x\n", evt->event_id);
	switch (evt->event_id) {
		case EVENT_STAMODE_CONNECTED:
			printf("connect to ssid %s, channel %d\n",
			evt->event_info.connected.ssid,
			evt->event_info.connected.channel);
		break;
		case EVENT_STAMODE_DISCONNECTED:
			printf("disconnect from ssid %s, reason %d\n",
			evt->event_info.disconnected.ssid,
			evt->event_info.disconnected.reason);
		break;
		case EVENT_STAMODE_AUTHMODE_CHANGE:
			printf("mode: %d -> %d\n",
			evt->event_info.auth_change.old_mode,
			evt->event_info.auth_change.new_mode);
		break;
		case EVENT_STAMODE_GOT_IP:
			printf("ip:" IPSTR ",mask:" IPSTR ",gw:" IPSTR,
			IP2STR(&evt->event_info.got_ip.ip),
			IP2STR(&evt->event_info.got_ip.mask),
			IP2STR(&evt->event_info.got_ip.gw));
			printf("\n");
		break;
		case EVENT_SOFTAPMODE_STACONNECTED:
			printf("station: " MACSTR "join, AID = %d\n",
			MAC2STR(evt->event_info.sta_connected.mac),
			evt->event_info.sta_connected.aid);
		break;
		case EVENT_SOFTAPMODE_STADISCONNECTED:
			printf("station: " MACSTR "leave, AID = %d\n",
			MAC2STR(evt->event_info.sta_disconnected.mac),
			evt->event_info.sta_disconnected.aid);
		break;
		default:
		break;
	}
}
void  vTask_WebServer( void * pvParameters )
{
	int listenfd;
	int ret = 0;
	int coon = 0;
	char buff[20] = {0};

	printf("phttp_dat.bit_rate=%d\n",phttp_dat.bit_rate);
	do
	{
		listenfd = socket(AF_INET,  SOCK_STREAM, 0);
		if (listenfd < 0) 
		{
			vTaskDelay(1000/portTICK_RATE_MS);
		}
	}while(listenfd < 0);


	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	do
	{
		ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
		if (ret != 0) 
		{
			vTaskDelay(1000/portTICK_RATE_MS);
		}
	}while(ret != 0);
	

	do
	{
		ret = listen(listenfd, 5);
		if (ret != 0) 
		{
			vTaskDelay(1000/portTICK_RATE_MS);
		}
	}while(ret != 0);
	
	printf("ready tcp\n");
	
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);

	while(1)
	{
		
		coon = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen);
		if(coon < 0)
		{
			vTaskDelay(1000/portTICK_RATE_MS);
			continue;
		}
		printf("accept success\n");
		while(1) 
		{
			memset(tcp_msg, 0, sizeof(tcp_msg));
			int ret = read(coon, tcp_msg, sizeof(tcp_msg));

			if(ret <= 0)
			{
				printf("you qing xia yi wei\n");
				close(coon);
				break;
			}
			else
			{
				printf("recv = \n -%s-\n",tcp_msg);
								
				if(strlen(tcp_msg) == 0)
				{
					close(coon);
					break;
				}
				//http_Handle(tcp_msg);
				string_Clear(window_1Str1_1,363);
				sprintf(window_1Str1_1,window_1Str1,".",".",".",".");

				string_Clear(window_1Str2_1,303);
				sprintf(window_1Str2_1,window_1Str2,"NON","ADD","DDD","EEE","FFF");

				    string_Clear(Window_2Str1_1,293);
				    sprintf(Window_2Str1_1,Window_2Str1,"GGG","HHH","III");

				    string_Clear(Window_3Str1_1,534);
				    sprintf(Window_3Str1_1,Window_3Str1,"JJJ","KKK","LLL","MMM","NNN","OOO","PPP");

					string_Clear(http_webStr,4069);
					sprintf(http_webStr,"%s%s%s%s%s%s%s%s",http_headStr,
							window_1Str1_1, window_1Str2_1,//´°¿Ú1
							Window_2Str1_1,//´°¿Ú2
							Window_3Str1_1,//´°¿Ú3
							window_5Str1,
							http_tailStr);
					write(coon, http_webStr, strlen(http_webStr));

			}
		}
	}
}
