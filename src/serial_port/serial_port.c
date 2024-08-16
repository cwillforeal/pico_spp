/* serial_port.c */
#include "serial_port.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

/* TODO: Figure out do we want to make this configurable */
#define UART_ID uart0
#define BAUD_RATE 115200

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

/* sp_init - Initalizes the serial port for usage
 */
void sp_init(void)
{
	// Set up our UART with the required speed.
	uart_init(UART_ID, BAUD_RATE);

	// Set the TX and RX pins by using the function select on the GPIO
	// Set datasheet for more information on function select
	gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
	gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}
/* sp_write_data - Writes out a buffer over the serial port
 * data_p - the data to write
 * size - how much data to write
 */
void sp_write_data(const char* data_p, uint32_t size)
{
	for(uint32_t i = 0; i < size; i++)
	{
		uart_putc_raw(UART_ID, data_p[i]);
	}
}
/* sp_read_data - Reads all data and sends it over the serial port
 * read_buff_p - pointer to write the data to
 * max_len - maximum amount of bytes that can be read
 * return - Total bytes read
 */
uint32_t sp_read_data(char* read_buff_p, uint32_t max_len)
{
	uint32_t size = 0;

	while(uart_is_readable(UART_ID) && (size < max_len))
	{
		read_buff_p[size++] = uart_getc(UART_ID);
	}
	return size;
}