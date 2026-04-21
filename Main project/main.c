#include <LPC21xx.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "esp.h"
#define LED 1<<7

int main()
{
	int temp;
	char data[100];
	char len_buf[5];

	IODIR0 = LED;

	
	delay(2000);
	uart_init();
	adc_init();
	uart_str("AT\r\n");
	while(!(ESP_waitfor("OK")));
	IOSET0 = LED;

	ESP_cmd("AT+CWMODE=1\r\n",2000);
	ESP_cmd("AT+CWJAP=\"Sri\",\"srisurya\"\r\n",8000);
	ESP_cmd("AT+CIPMUX=0\r\n",2000);

	while(1)
	{
		temp=((adc_read())*3.3*100)/1024;
		sprintf(data,"GET /update?api_key=5YFAGY98K9AV8DSO&field1=%d\r\n",temp);
		ESP_cmd("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n",4000);
		sprintf(len_buf,"%d",strlen(data));
		uart_str("AT+CIPSEND=");
		uart_str(len_buf);
		uart_str("\r\n");
		delay(2000);

		uart_str(data);
		delay(5000);

		ESP_cmd("AT+CIPCLOSE\r\n",2000);
		delay(15000);

	}
}
