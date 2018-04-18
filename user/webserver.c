#include "esp_common.h"
#include "para.h"
#include "webserver.h"

char http_webStr[4096] = {0};//4
char window_5Str1_1[299] = {0};
char window_4Str1_1[452] = {0};
char Window_3Str1_1[534] = {0};
char Window_2Str1_1[293] = {0};
char window_1Str2_1[303] = {0};
char window_1Str1_1[363] = {0};
http_dat phttp_dat;

const char http_headStr[318]=				//网页头
		"HTTP/1.1 200 OK\r\nContent-Type: text"
		"/html\r\nContent-Length: 2500\r\n\r\n"
		"<meta http-equiv=\"Content-Type\"content=\"text/html; charset=gb2312\" />"
			"<title>测试网页</title>"
		"<style type=\"text/css\">"
		"<!--"
		"body,td,th{"
			"font-size: x-large;"
			"color: #FF0000;"
			"font-weight: bold;"
		"}"
		"body{"
			"background-color: #CCCCCC;"
		"}"
		"-->"
		"</style>"
			"</head>"
		"<html>"
		"<body>"
		;



const char window_1Strico[363]=	//窗口1第一帧数据 波特率
		"<form id=\"form1\" name=\"form1\" method=\"post\" action=\"\">"
		  "<p align=\"center\">"
		   " <input type=\"submit\" name=\"Submit3\" value=\"Refresh\" />"
		  "</p>"
		  ;
const char http_tailStr[14]=  //网页尾
		"</body>"
		"</html>";



const char window_1Str1[363]=	//窗口1第一帧数据 波特率
		"<form id=\"form1\" name=\"form1\" method=\"post\" action=\"\">"
		  "<p align=\"center\">"
		   " <input type=\"submit\" name=\"Submit3\" value=\"Refresh\" />"
		  "</p>"
		  "<p>波特率"
		    "<select name=\"select\">"
		      "<option value=\"rate_1200\"%s>1200</option>"
		      "<option value=\"rate_9600\"%s>9600</option>"
		      "<option value=\"rate_57600\"%s>57600</option>"
		      "<option value=\"rate_115200\"%s>115200</option>"
		    "</select>"
		;


const char window_1Str2[303]=		//窗口1第二帧数据 校验/停止位
		"校验位"
		"<select name=\"select3\">"
		  "<option value=\"None_0\"%s>None</option>"
		  "<option value=\"None_1\"%s>Odd</option>"
		  "<option value=\"None_2\"%s>Even</option>"
		"</select>"
		"停止位"
		"<select name=\"select4\">"
		  "<option value=\"stop_0\"%s>1</option>"
		  "<option value=\"stop_1\"%s>2</option>"
		"</select>"
		  "</p>"
		;



const char Window_2Str1[293]=
		" <p>STA:"
		  "SSID"
		  "<input name=\"STA_SSID\" type=\"text\" value=\"%s\"maxlength=\"15\" />"
		  "PASS"
		  "<input name=\"STA_PASS\" type=\"text\" value=\"%s\" maxlength=\"15\" /> "
		    "<input name=\"checkbox\" type=\"checkbox\" value=\"STA_CONN\" %s/>"
		  "是否启用连接</p>"
		  ;



const char Window_3Str1[534]=
		"<p>AP:"
		  "AP_SSID"
		  "<input name=\"AP_SSID\" type=\"text\" value=\"%s\" maxlength=\"15\" /> "
		  "AP_PASS"
		  "<input name=\"AP_PASSWORD\" type=\"text\" value=\"%s\" maxlength=\"15\" />"
		  "加密方式"
		    "<select name=\"select5\">"
		      "<option value=\"AP_OPEN\"%s>OPEN</option>"
		      "<option value=\"AP_WPA\"%s>WPA</option>"
		      "<option value=\"AP_WPA2\"%s>WPA2</option>"
		      "<option value=\"AP_WPA_WPA2\"%s>WPA_WPA2</option>"
		    "</select>"
		  "隐藏 SSID"
		    "<input name=\"AP_hidden\" type=\"checkbox\" value=\"AP_hidde\"%s />"
		  "</p>"
		;


const char window_4Str1[452]=
		"<p>TCP/UDP: "
		    "<select name=\"select6\">"
		      "<option value=\"TX_TCP\" %s>TCP</option>"
		      "<option value=\"TX_UDP\"%s>UDP</option>"
		    "</select>"
		  "Service/Client:"
		    "<select name=\"select7\">"
		      "<option value=\"AP_Service\"%s>Service</option>"
		      "<option value=\"STA_Client\"%s>Client</option>"
		    "</select>"
		"</p>"
		  "<p>IP:"
		    "<input name=\"TX_IP\" type=\"text\" value=\"%s\" maxlength=\"15\" />"
		  "PORT:"
		  "<input name=\"TX_PORT\" type=\"text\" value=\"%s\" maxlength=\"4\" />"
		 " </p>"
		;


const char window_5Str1[299]=
		"<p>test</p>"
		"<p></p>"
		  "<p>"
		    "<input name=\"Submit\" type=\"submit\" value=\"configure_\" />"
		  "</p>"
		  "<p>"
		    "<input type=\"submit\" name=\"Submit2\" value=\"Restore_\" />"
		  "</p>"
		;
/*
 * 函数：void GetString(char *arg ,char *dat,char *data)
 * 功能:获取已知字符串值
 * arg：字符串 dat:已知字符串 data:获取的位置
 */
void GetString(char *arg ,char *dat,char *data)//获取字符串
{
	char len;
	char *buff=NULL;
	len=strlen(dat);
	buff= (char *)strstr(arg,dat);
	buff=buff+len+1;
	while(*buff!='&')
	{
		*data=*buff;
		data++;
		buff++;
	}
}

/*
 * 函数:char Seek_Str(char *s ,char *d) //寻找字符串
 * 功能:判断s是否包含d有字符串包含返回:1否则:0
 */
char Seek_Str(char *s ,char *d) //寻找字符串
{
	char *pbuffer = NULL;
	 pbuffer=(char *)strstr(s,d);
	 if(pbuffer!=NULL)
	 {
		 return 1;
	 }
	 else
	 {
		 return 0;
	 }
}


void string_Clear(char *arg ,uint16_t len)
{
	for(;len>0;len--)
	{
		arg[len]=0x00;
	}
}


void window_Rate(char *arg)
{
	if(Seek_Str(arg,"configure_"))
	{
		if(Seek_Str(arg,"rate_1200")){phttp_dat.bit_rate=1200;}
		if(Seek_Str(arg,"rate_9600")){phttp_dat.bit_rate=9600;}
		if(Seek_Str(arg,"rate_57600")){phttp_dat.bit_rate=57600;}
		if(Seek_Str(arg,"rate_115200")){phttp_dat.bit_rate=115200;}
		if(Seek_Str(arg,"None_0")){phttp_dat.bit_jiao=2;}
		if(Seek_Str(arg,"None_1")){phttp_dat.bit_jiao=1;}
		if(Seek_Str(arg,"None_2")){phttp_dat.bit_jiao=0;}

		if(Seek_Str(arg,"stop_0")){phttp_dat.bit_stop=1;}
		if(Seek_Str(arg,"stop_1")){phttp_dat.bit_stop=3;}
		char snum[15];
		char pnum[15];
		//获取STA的ssid 和PASSWORD
		string_Clear(snum,15);string_Clear(pnum,15);//清楚缓存器
		GetString(arg,"STA_SSID",snum);				//提取ssid字符串
		GetString(arg,"STA_PASS",pnum);			//提取ssid字符串
		strcpy(phttp_dat.sta_ssid,snum);
		strcpy(phttp_dat.sta_password,pnum);
		if(Seek_Str(arg,"STA_CONN")){phttp_dat.sta_connflag=1;}else{phttp_dat.sta_connflag=0;}
		//获取AP的ssid和PASSWORD
		string_Clear(snum,15);string_Clear(pnum,15);//清楚缓存器
		GetString(arg,"AP_SSID",snum);				//提取ssid字符串
		GetString(arg,"AP_PASSWORD",pnum);			//提取ssid字符串
		string_Clear(phttp_dat.ap_ssid,15);string_Clear(phttp_dat.ap_password,15);
		strcpy(phttp_dat.ap_ssid,snum);
		strcpy(phttp_dat.ap_password,pnum);
		if(Seek_Str(arg,"AP_OPEN")){phttp_dat.ap_en=0;}
		if(Seek_Str(arg,"AP_WPA")){phttp_dat.ap_en=1;}
		if(Seek_Str(arg,"AP_WPA2")){phttp_dat.ap_en=2;}
		if(Seek_Str(arg,"AP_WPA_WPA2")){phttp_dat.ap_en=3;}
		if(Seek_Str(arg,"AP_hidde")){phttp_dat.ap_hidde=1;}else{phttp_dat.ap_hidde=0;}
//
		//判断是TCP 还是UDP
		if(Seek_Str(arg,"TX_TCP")){phttp_dat.TCP_UDP=1;}else{phttp_dat.TCP_UDP=0;}
		//判断是否为服务器
		if(Seek_Str(arg,"AP_Service")){phttp_dat.Service_Client=1;}else{phttp_dat.Service_Client=0;}
//		//获取IP
		char ipnum[15];
		string_Clear(ipnum,15);
		GetString(arg,"TX_IP",ipnum);
		string_Clear(phttp_dat._IP,15);
		strcpy(phttp_dat._IP,ipnum);		//IP
		string_Clear(phttp_dat._port,4);
		GetString(arg,"TX_PORT",phttp_dat._port);		//port
//		os_strcpy(phttp_dat._port,sport);
		phttp_dat.flash_flag=0;
		EEPROM_Write();
		system_restart();
	}
}



void  http_Handle(char *arg) //字符串的解析
{
	if((Seek_Str(arg,"GET")==0)&&(!Seek_Str(arg,"HTTP/1.1")==0))
	{
		if(Seek_Str(arg,"POST / HTTP/1.1"))
		{
			window_Rate(arg);
		}
	}

}

void EEPROM_Read()
{
	spi_flash_read(100 * 4096, (uint32 *)&phttp_dat, sizeof(http_dat));
}

void EEPROM_Write()
{
	spi_flash_erase_sector(100);
	spi_flash_write(100 * 4096,(uint32 *)&phttp_dat,sizeof(http_dat));
}


