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
    // printf("WS2812 Smoke Test, using pin %d", WS2812_PIN);

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    turn_on_power();
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    // int i = 0;
    // int pixel_grb = 0x00000000;
    // while (true) {
    //     sleep_ms(100);
    //     i++;
    //     if(i >= 3){
    //         i = 0;
    //     }
    //     if(i == 0){
    //         pixel_grb = 0x00ff00ff;
    //     }
    //     if(i ==1){
    //         pixel_grb = 0x004500ab;
    //     }
    //     if(i == 2){
    //         pixel_grb = 0x000088aa;
    //     }
    //     printf("Hello, world! The rgb is %d\n", pixel_grb);
    //     set_neopixel_color(pixel_grb);
    // }
    const uint LED_PIN_RED = 4;      
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    const uint LED_PIN_YELLOW = 6;      
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    const uint LED_PIN_GREEN = 5;      
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    while (true) {
        // the loop would be: red on for 3s, 
        // then yellow blinks for 1s,
        // then green on for 3s

        // RED
        gpio_put(LED_PIN_RED, 1);
        gpio_put(LED_PIN_YELLOW, 0);
        gpio_put(LED_PIN_GREEN, 0);
        printf("Wait!\n");
        sleep_ms(3000);

        // YELLOW
        int i = 0;
        while(i<=4){
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_YELLOW, 1);
            gpio_put(LED_PIN_GREEN, 0);
            sleep_ms(100);
            gpio_put(LED_PIN_YELLOW,0);
            sleep_ms(100);
            i+=1;
        }

        // GREEN
        gpio_put(LED_PIN_RED, 0);
        gpio_put(LED_PIN_YELLOW, 0);
        gpio_put(LED_PIN_GREEN, 1);
        printf("Ready to go!\n");
        sleep_ms(3000);
    }
    return 0;
}
