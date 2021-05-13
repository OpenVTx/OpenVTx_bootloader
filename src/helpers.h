#pragma once

#include <stddef.h>

#define WORD_ALIGNED_ATTR   __attribute__((aligned(32)))

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

extern uint32_t millis(void);
extern void delay(uint32_t const ms);
extern void delayMicroseconds(uint32_t us);
