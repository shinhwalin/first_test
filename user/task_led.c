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
#include "gpio.h"
void  vTask_led( void * pvParameters )
{
	GPIO_ConfigTypeDef pin;
	pin.GPIO_Pin = (0x01 << 15);
	pin.GPIO_Mode = GPIO_Mode_Output;
	pin.GPIO_Pullup = GPIO_PullUp_DIS;
	pin.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
	gpio_config(&pin);

	pin.GPIO_Pin = (0x01 << 14);
	pin.GPIO_Mode = GPIO_Mode_Output;
	pin.GPIO_Pullup = GPIO_PullUp_DIS;
	pin.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
	gpio_config(&pin);

	pin.GPIO_Pin = (0x01 << 13);
	pin.GPIO_Mode = GPIO_Mode_Output;
	pin.GPIO_Pullup = GPIO_PullUp_DIS;
	pin.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
	gpio_config(&pin);

	GPIO_AS_OUTPUT(13);//b
	GPIO_AS_OUTPUT(14);//r
	GPIO_AS_OUTPUT(15);//g
	while(1)
	{
//		printf("led task\r\n");
/*		GPIO_OUTPUT_SET(13,0);
		vTaskDelay(10);
		GPIO_OUTPUT_SET(14,0);
		vTaskDelay(10);
		GPIO_OUTPUT_SET(15,0);
		vTaskDelay(10);
		GPIO_OUTPUT_SET(13,1);
		vTaskDelay(10);
		GPIO_OUTPUT_SET(14,1);
		vTaskDelay(10);
		GPIO_OUTPUT_SET(15,1);
*/
		vTaskDelay(10);
	}

}

