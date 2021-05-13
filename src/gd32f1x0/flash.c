#include "flash.h"
#include "main.h"
#include "serial.h"
#include "helpers.h"
#include <string.h>

/* Function pointer for jumping to user application. */
typedef void (*fnc_ptr)(void);


int flash_erase_page(uint32_t address)
{
    return flash_storage_erase(address, PAGE_SIZE);
}

int flash_storage_erase(uint32_t address, uint32_t size)
{
    if (address < ((uint32_t)&__APP_START) || FLASH_END <= address)
        return -1;

    /* Use size as a end address */
    size = address + size;

    /* unlock the flash program/erase controller */
    fmc_unlock();

    /* clear all pending flags */
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);

    /* erase the flash pages */
    for (; address < size; address += PAGE_SIZE) {
        if (fmc_page_erase(address) != FMC_READY) {
            break;
        }
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
        fwdgt_counter_reload();
    }

    /* lock the main FMC after the erase operation */
    fmc_lock();

    return (address >= size) ? 0 : -1;
}


int flash_storage_write(uint32_t address, uint32_t const * data, uint32_t size)
{
    if (address < ((uint32_t)&__APP_START) || FLASH_END <= address)
        return -1;
    if (!data || !size || APP_SIZE < (size * 4U))
        return -1;

    /* unlock the flash program/erase controller */
    fmc_unlock();

    /* program flash */
    while (size-- && address < FLASH_END) {
        if (fmc_word_program(address, *data++) != FMC_READY) {
            goto flash_write_fail;
        }
        address += 4U;
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
        fwdgt_counter_reload();
    }

    /* lock the main FMC after the program operation */
    fmc_lock();

    return 0;

flash_write_fail:
    return -1;
}


int8_t flash_check_app_loaded(void)
{
    /* Check if app is already loaded */
    __IO uint32_t const * vectors = (__IO uint32_t *)(APP_START_ADDR);
    extern uint32_t _vectors_start;
    extern uint32_t _vectors_end;
    uint32_t address;
    uint32_t count = ((uint32_t)&_vectors_end - (uint32_t)&_vectors_start);
    count /= sizeof(uint32_t);
    count--;

    /* Validate stack address first */
    if ((uint16_t)(*vectors++ >> 20) != 0x200)
        goto exit_fail;

    /* Validate vector table */
    while (count--) {
        address = *vectors++;
        address >>= 16;
        if ((address != 0x800) && (address != 0))
            goto exit_fail;
    }

    return 0;

exit_fail:
    return -1;
}


/**
 * @brief   Actually jumps to the user application.
 * @param   void
 * @return  void
 */
void flash_jump_to_app(void)
{
    fwdgt_counter_reload();
    status_led3(1);

    if (flash_check_app_loaded() < 0) {
        /* Restart if no valid app found */
        NVIC_SystemReset();
    }

    /* Small delay to allow UART TX send out everything */
    delay(100);

    /* Function pointer to the address of the user application. */
    fnc_ptr jump_to_app;
    jump_to_app = (fnc_ptr)(*(volatile uint32_t *)(APP_START_ADDR + 4u));
    /* Remove configs before jump. */
    serial_end();
    //HAL_DeInit();

    __disable_irq();

    /* Change the main stack pointer. */
    asm volatile("msr msp, %0" ::"g"(*(volatile uint32_t *)APP_START_ADDR));
    SCB->VTOR = (__IO uint32_t)(APP_START_ADDR);
    (void)SCB->VTOR;

    jump_to_app();

    while(1)
        ;
}
