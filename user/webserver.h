#ifndef YS_ESP_WEBSERVER_H
#define YS_ESP_WEBSERVER_H
#include "esp_common.h"
#include "para.h"
extern char http_webStr[4096];//4//4k
extern void string_Clear(char *arg ,uint16 len);
extern char Seek_Str(char *s ,char *d);

extern void GetString(char *arg ,char *dat,char *data);

extern void EEPROM_Read();

extern void EEPROM_Write();
extern void  http_Handle(char *arg);

#define select_show   "selected=\"selected\""
#define select_show1 "checked=\"checked\""

extern const char http_headStr[318];
extern const char http_tailStr[14];
extern const char window_1Str1[363];
extern const char window_1Str2[303];
extern const char Window_2Str1[293];
extern const char Window_3Str1[534];
extern const char window_4Str1[452];
extern const char window_5Str1[299];



extern char window_1Str1_1[363]; //波特率

extern char window_1Str2_1[303];//校验位

extern char Window_2Str1_1[293];//STA


extern char Window_3Str1_1[534];//AP

extern char window_4Str1_1[452];//TCP

extern char window_5Str1_1[299];


typedef struct {
		uint32 bit_rate; 	//波特率
		char  bit_jiao; 	//校验位
		char  bit_stop;		//停止位
		char sta_ssid[15]; 		//sta 账号
		char sta_password[15]; 	//sta 密码
		char sta_connflag;		//是否连接
		char ap_ssid[15];    	//ap  账号
		char ap_password[15];   //ap    密码
		char ap_en;            //ap加密方式
		char ap_hidde;			//是否隐藏SSID
		char TCP_UDP;          //通行协议 TCP UDP 0:UDP 1:TCP
		char Service_Client;	//0:Client 1:Service
		char _IP[15];
		char _port[4];		    //端口号
		uint16 _port2;
		char flash_flag;			//标志位
}http_dat;
extern http_dat phttp_dat;




#endif
