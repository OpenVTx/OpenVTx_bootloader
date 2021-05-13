#ifndef __SERIAL_H_
#define __SERIAL_H_

#include <stdint.h>

#define UART_ERROR ((uint8_t)-1)


void serial_begin(uint32_t baud, uint32_t tx_pin, uint32_t rx_pin, uint8_t stopbits);
void serial_end(void);
uint8_t serial_available(void);
uint8_t serial_read(void);
uint8_t serial_read_timeout(uint8_t *data, uint16_t length, uint16_t timeout);
void serial_write(uint8_t data);
void Serial_write_len(uint8_t *data, uint32_t size);
void serial_flush(void);

#endif /* __SERIAL_H_ */
