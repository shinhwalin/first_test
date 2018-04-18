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
#include "uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "webserver.h"

/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 user_rf_cal_sector_set(void)
{
    flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;
            break;

        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}

void AP_init()
{
	struct softap_config *config = (struct softap_config *)zalloc(sizeof(struct	softap_config)); // initialization
	wifi_softap_get_config(config); // Get soft-AP config first.
	sprintf(config->ssid, "test");
	sprintf(config->password, "11111111");
	config->authmode = AUTH_WPA_WPA2_PSK;
	config->ssid_len = 0; // or its actual SSID length
	config->max_connection = 4;
	wifi_softap_set_config(config); // Set ESP8266 soft-AP config
	free(config);
}
void STA_init()
{
	//ap config
	struct station_config * config = (struct station_config *)zalloc(sizeof(struct station_config));
	sprintf(config->ssid, "%s","TP-LINK-8266");
	sprintf(config->password, "852963741");
	wifi_station_set_config(config);
	free(config);
}

void ESP_sys_init()
{
		if(wifi_set_opmode_current(STATIONAP_MODE) == 0)
	{
		printf("wifi set mode 0x03 failed!\r\n");
		while(1);
	}
	printf("wifi set mode 0x03 success!\r\n");
	//EEPROM_Read();
	if(phttp_dat.flash_flag != 0){
		phttp_dat.bit_rate=9600;
		phttp_dat.bit_jiao=2;
		phttp_dat.bit_stop=1;
		strcpy(phttp_dat.sta_ssid,"smart123456");
		strcpy(phttp_dat.sta_password,"123456789");
		phttp_dat.sta_connflag=0;							//是否启动连接

		strcpy(phttp_dat.ap_ssid,"admin");
		strcpy(phttp_dat.ap_password,"123456789");
		phttp_dat.ap_en=0;
		phttp_dat.ap_hidde=0;

		phttp_dat.TCP_UDP=1; //默认TCP
		phttp_dat.Service_Client=1;//服务器模式
		strcpy(phttp_dat._IP,"192.168.16.101");	//客户端才用IP地址
		strcpy(phttp_dat._port,"8080");//端口8080
	}
	
	AP_init();
	//STA_init();
}



/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
#include "para.h"
struct esp_platform_saved_param sys_para;
//form document of the SDK,the task can be create from 1 to 9

extern void  vTask_WebServer( void * pvParameters );
extern void  vTask_station( void * pvParameters );
extern void  vTask_led( void * pvParameters );

void user_init(void)
{
	xTaskHandle xHandle = NULL;
	ESP_sys_init();
	uart_init_new();
	//xTaskCreate(
        //            vTask_station,       /* Function that implements the task. */
        //            "station_task",          /* Text name for the task. */
        //            512,      /* Stack size in words, not bytes. */
        //            NULL,    /* Parameter passed into the task. */
        //            2,/* Priority at which the task is created. */
        //            &xHandle );      /* Used to pass out the created task's handle. */
	
	xTaskCreate(
                    vTask_WebServer,       /* Function that implements the task. */
                    "vTask_WebServer",          /* Text name for the task. */
                    512,      /* Stack size in words, not bytes. */
                    NULL,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &xHandle );      /* Used to pass out the created task's handle. */
}

