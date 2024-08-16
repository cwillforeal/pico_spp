/* serial_port.h
 */
#include <stdint.h>
#include "hardware/uart.h"

void sp_init(void);
void sp_write_data(const char* data_p, uint32_t size);
uint32_t sp_read_data(char* read_buff_p, uint32_t max_len);
