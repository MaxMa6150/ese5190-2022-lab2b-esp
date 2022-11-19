/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "ws2812.h"

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "registers.h"

#define IS_RGBW true
#define NUM_PIXELS 150

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else

// default to pin 2 if the board doesn't have a default WS2812 pin defined

#define WS2812_PIN 12
#define WS2812_POWER_PIN 11
#endif



int main() {
    stdio_init_all();

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    turn_on_power();
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);


    uint32_t input_address = 0x00000000;
    ADDRESS address = 0x00000000;
    VALUE value;
    int mode;

    while (true) {
        printf("Start. \n");

        // address selection
        printf("Enter an address you want to read/write: \n");
        scanf("%x", &input_address);  
        printf("Address is %x\n",input_address);
        address = (ADDRESS) input_address;

        // mode selection
        printf("Enter a mode you want to operate (0 for read/1 for write): \n");
        scanf("%d", &mode);
        
        // reading mode
        if(mode == 0) {
            printf("The data read is: %x\n", register_read(address));
        }
        // writing mode
        else {
            // value input
            printf("Enter an value you want to write in: \n");
            scanf("%x", &value);  
            printf("Value is %x \n",value);
            register_write(address, value);
            printf("The value written in: %x\n", register_read(address));
        }
        sleep_ms(250);

    }

    return 0;
    // uint32_t addr_input = 0x00000000;
    // ADDRESS addr = 0x00000000;
    // VALUE data;
    // int opt;

    // // while (!stdio_usb_connected());

    // while (true) {
    //     printf("New Program start: \n");
    //     printf("Input a register address you would like to read/write: \n");
    //     scanf("%x", &addr_input);
    //     printf("Confirmation of address: %x\n", addr_input);
    //     addr = (ADDRESS) addr_input;
    
    //     printf("Input 0 for reading and 1 for writing: \n");
    //     scanf("%d", &opt);
    //     if(opt == 0) {
    //         printf("The data read is: %x\n", register_read(addr));
    //     } else {
    //         printf("Type in the data you want to write into the address: \n");
    //         scanf("%x", &data);
    //         register_write(addr, data);
    //         printf("Confirmation of data written in: %x\n", register_read(addr));
    //     }
    //     sleep_ms(250);

    // }

    // return 0;

}
