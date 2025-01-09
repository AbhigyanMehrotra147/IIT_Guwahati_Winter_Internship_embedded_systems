#include <reg51.h>

sbit LED = P1^1;

void UART_Init(void);
void UART_Tx(char);  // Explicit parameter name in prototype
char UART_Rx(void);

void main(void)
{
    char received_char;

    UART_Init();

    while (1)
    {
        UART_Tx('A');
        received_char = UART_Rx();
        if (received_char == 'B')
        {
            LED = 1;
        }
        else
        {
            LED = 0;
        }
    }
}

// Establishing UART
void UART_Init(void)
{
    TMOD = 0x20;  // Timer 1 in Mode 2 (8-bit auto-reload)
    TH1 = -3;   // Baud rate 9600 for 11.0592 MHz
    SCON = 0x50;  // Serial mode 1, REN enabled
    TR1 = 1;      // Start Timer 1
}

// Transmitting
void UART_Tx(char data)  // Match the prototype
{
    SBUF = data;
    while (TI == 0);  // Wait for transmission to complete
    TI = 0;           // Clear transmit interrupt flag
}

// Receiving
char UART_Rx(void)
{
    while (RI == 0);  // Wait for reception to complete
    RI = 0;           // Clear receive interrupt flag
    return SBUF;      // Return received data
}
