#include <lpc21xx.h>
#include <stdio.h>

// -------- Delay --------
void delay(unsigned int d)
{
    unsigned int i, j;
    for(i=0;i<d;i++)
        for(j=0;j<1000;j++);
}

// -------- UART --------
void UART0_Init()
{
    PINSEL0 |= 0x00000005;   // TXD0, RXD0

    U0LCR = 0x83;            // 8-bit, 1 stop, DLAB=1
    U0DLL = 97;              // 9600 baud (15MHz)
    U0DLM = 0;
    U0LCR = 0x03;            // DLAB=0
}

void UART0_TxChar(char ch)
{
    while (!(U0LSR & (1 << 5)));
    U0THR = ch;
}

void UART0_TxString(char *str)
{
    while (*str)
        UART0_TxChar(*str++);
}

// -------- ADC --------
void ADC_Init()
{
    PINSEL1 |= (1 << 24);   // P0.28 as AD0.1
    AD0CR = (1 << 1) | (4 << 8) | (1 << 21);
}

unsigned int ADC_Read()
{
    AD0CR |= (1 << 24);  // Start
    while (!(AD0GDR & (1 << 31))); // Wait DONE
    return (AD0GDR >> 6) & 0x3FF;
}

// -------- ESP Commands --------
void ESP_Send(char *cmd, unsigned int delay_time)
{
    UART0_TxString(cmd);
    delay(delay_time);
}

// -------- MAIN --------
int main()
{
    char buffer[100];
    unsigned int adc_value;

    UART0_Init();
    ADC_Init();

    delay(2000);

    // ESP Setup
    ESP_Send("AT\r\n", 2000);
    ESP_Send("AT+CWMODE=1\r\n", 2000);
    ESP_Send("AT+CWJAP=\"YOUR_SSID\",\"YOUR_PASS\"\r\n", 5000);

    while(1)
    {
        adc_value = ADC_Read();

        // Start TCP connection
        ESP_Send("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n", 3000);

        // Prepare HTTP GET request
        sprintf(buffer,
        "GET /update?api_key=YOUR_API_KEY&field1=%d\r\n",
        adc_value);

        // Tell ESP how many bytes we send
        ESP_Send("AT+CIPSEND=60\r\n", 2000);

        // Send actual data
        ESP_Send(buffer, 3000);

        ESP_Send("AT+CIPCLOSE\r\n", 2000);

        delay(15000); // ThingSpeak delay
    }
}
