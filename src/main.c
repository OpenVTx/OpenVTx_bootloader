#include "serial.h"
#include "gpio.h"
#include "flash.h"
#include "xmodem.h"
#include "helpers.h"


#define UART_RX     PA9
#define UART_TX     PA9
#define LED1        PA4 // Red
#define LED2        PA3 // Green
#define LED3        PA2 // Blue

#ifndef BAUD_RATE
//#define BAUD_RATE   115200
#define BAUD_RATE   4800
#endif // BAUD_RATE


static uint32_t boot_start_time;


#ifdef LED1
static gpio_out_t led1_pin;
#endif
#ifdef LED2
static gpio_out_t led2_pin;
#endif
#ifdef LED3
static gpio_out_t led3_pin;
#endif

void status_leds_init(void)
{
#ifdef LED1
    led1_pin = gpio_out_setup(LED1, 0);
#endif
#ifdef LED2
    led2_pin = gpio_out_setup(LED2, 0);
#endif
#ifdef LED3
    led3_pin = gpio_out_setup(LED3, 0);
#endif
}

void status_led1(uint8_t const state)
{
#ifdef LED1
    gpio_out_write(led1_pin, state);
#else
    (void)state;
#endif
}

void status_led2(uint8_t const state)
{
#ifdef LED2
    gpio_out_write(led2_pin, state);
#else
    (void)state;
#endif
}

void status_led3(uint8_t const state)
{
#ifdef LED3
    gpio_out_write(led3_pin, state);
#else
    (void)state;
#endif
}


#define BOOTLOADER_KEY  0x4f565458 // OVTX
#define BOOTLOADER_TYPE 0xACDC

struct bootloader {
    uint32_t key;
    uint32_t reset_type;
    uint32_t baud;
};

static int check_bootloader_data(void)
{
    /* Fill reset info into RAM for bootloader */
    extern uint32_t _bootloader_data;
    struct bootloader * blinfo = (struct bootloader*)&_bootloader_data;
    if ((BOOTLOADER_KEY == blinfo->key) && (BOOTLOADER_TYPE == blinfo->reset_type)) {
        // Clear data
        blinfo->key = 0;
        blinfo->reset_type = 0;
        return blinfo->baud; // bootloader requested
    }
    if (flash_check_app_loaded() < 0)
        return BAUD_RATE; // No valid code => stay in bootloader
    return -1; // boot into main code
}


void setup(void)
{
    fwdgt_config(0x0FFF, FWDGT_PSC_DIV4);
    fwdgt_window_value_config(0x0FFF);
    fwdgt_enable(); // Enable watchdog
    status_leds_init();

    /* Reset WD */
    fwdgt_counter_reload();

    int baudrate = check_bootloader_data();

    /* Check if the bootloader update was requested */
    if (0 <= baudrate) {
        uint8_t stopbits = 2;
        switch (baudrate) {
            case 4800: // SA
                break;
            case 9600: // TRAMP and MSP
                stopbits = 1;
                break;
#if BAUD_RATE != 4800 && BAUD_RATE != 9600
            case BAUD_RATE:
#endif
                break;
            default:
                baudrate = BAUD_RATE;
                break;
        };
        serial_begin(baudrate, UART_TX, UART_RX, stopbits);

        boot_start_time = millis();

        xmodem_receive();
    }
    /* Jump into applicaiton code */
    flash_jump_to_app();
}

void loop(void)
{
}
