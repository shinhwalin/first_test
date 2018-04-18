#ifndef PARA_H
#define PARA_H
struct esp_platform_saved_param {
    uint8 ssid[40];
    uint8 password[40];

};
#define ESP_PARAM_START_SEC		(0xFE -  4)//before master_device_key.bin 

bool read_para(struct esp_platform_saved_param * data);
bool save_para(struct esp_platform_saved_param * data);
#endif

