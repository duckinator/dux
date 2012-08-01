/*
 * This code is based on information from
 * http://www.nondot.org/sabre/os/files/Communication/ser_port.txt
 */

#include <module.h>
#include <lib/krnllib.h>
#include <system.h>

#include <driver/uart.h>

//DRIVER_INIT(UartInit)
//void _start(void) { UartInit(); }

void UartSend(char c)
{
	if (c == '\n')
		UartSend_int('\r');
	UartSend_int(c);
}

void UartSendString(const char *str)
{
	do {
		UartSend(*str);
	}	while (*str++);
}

static void UartSend_int(char c)
{
	/* wait until UART is ready to send */
	while ((HalInPort(UART_BASE_REGISTER + LineStatus) & THRE) == 0);

	HalOutPort(UART_BASE_REGISTER, (uint8_t)c);
}

MODULE(Uart)
{
	HalOutPort(UART_BASE_REGISTER + LineControl, DLAB);
	HalOutPort(UART_BASE_REGISTER, UART_BAUDRATE_DIVISOR);
	HalOutPort(UART_BASE_REGISTER + LineControl, UART_LCR);
	HalOutPort(UART_BASE_REGISTER + ModemControl, 0);

	UartSendString("UART successfully enabled.\n");

	return 0;
}

struct DisplayDevice UartDisplayDevice = {
	.Init		= (void*)Uart__ModuleInit,
	.DisplayChar	= (void*)UartSend,
	.DisplayClear	= NULL,	/* nothing, for now */
};
