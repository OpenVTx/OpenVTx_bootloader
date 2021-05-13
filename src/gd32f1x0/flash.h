#pragma once

#include <gd32f1x0.h>
#include <stdint.h>

#define APP_START_ADDR (((uint32_t)&__APP_START))
#define APP_SIZE       (uint32_t)((uint8_t*)&__APP_END - (uint8_t*)&__APP_START)

#define FLASH_END      ((uint32_t)&__APP_END)
#define PAGE_SIZE      ((uint32_t)&__FLASH_PAGE_SIZE)

extern __IO uint32_t __APP_START;
extern __IO uint32_t __APP_END;
extern __IO uint32_t __FLASH_PAGE_SIZE;


int flash_erase_page(uint32_t address);

int flash_storage_erase(uint32_t address, uint32_t size);
int flash_storage_write(uint32_t address, uint32_t const * data, uint32_t size);


int8_t flash_check_app_loaded(void);
void flash_jump_to_app(void);
