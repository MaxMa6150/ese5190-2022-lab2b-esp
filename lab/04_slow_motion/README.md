### TODO:

Update your sequencer to be able to slow down and speed up recordings/replay. On the input side, the goal is ultimately to be able to handle the full 4 Gbps "firehose" from the PIO logic analyzer example in the SDK manual, which would fill up 256Kb of RAM in only 31 µs at a system clock speed of 125000 MHz if captured 'raw'! On the output side, the goal is to be able to output precisely timed sequences from the PIO at system clock resolution based on a handful of control points.

- update your sequencer to be able to record just the timestamped transitions between input values, and to be able to play data in this format
- give your sequencer the ability to select a range of output rates for both live and recorded input


### Code:

The speed up/down options are included in Part 3 code. The code below is .c file running on PY2040, and the code .py running on PC is attached in Part 3

```
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "ws2812.h"

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define IS_RGBW true
// #define NUM_PIXELS 150

// #ifdef PICO_DEFAULT_WS2812_PIN
// #define WS2812_PIN PICO_DEFAULT_WS2812_PIN
// #else

// // default to pin 2 if the board doesn't have a default WS2812 pin defined

#define WS2812_PIN 12
#define WS2812_POWER_PIN 11
#define PIO pio0
#define SM 0
#define FREQ 800000
// #define MAX 100
// #endif

#define record 'r'
#define replay 'p'
#define BOOT_PIN 21


int main() {
    stdio_init_all();
    uint offset = pio_add_program(PIO, &ws2812_program);
    turn_on_power();
    ws2812_program_init(PIO, SM, offset, WS2812_PIN, FREQ, IS_RGBW);

    gpio_init(BOOT_PIN);
    gpio_set_dir(BOOT_PIN, GPIO_IN);

    uint32_t key = 0x00000000;
    uint32_t flag = 0x00000000;

    // int array[MAX]={0};
    // int i;
    while(true){
        key = getchar_timeout_us(0);
        // while(stdio_usb_connected()!=true);
        switch(key){
            case 'r':
                set_neopixel_color(0X00FF0000);
                sleep_ms(1000);
                // printf("Start the recording after red light:\n");
                // set_neopixel_color(0X00FF0000);
                // sleep_ms(1000);
                while(true){
                    flag = 0x00000000;
                    flag = getchar_timeout_us(0);
                    if(!gpio_get(BOOT_PIN)) {
                        printf("1\n");
                        set_neopixel_color(0X0000FF00);
                    } 
                    else {
                        printf("0\n");
                        set_neopixel_color(0x00000000);
                    }
                    if(flag == 'N'){
                        set_neopixel_color(0X00000000);
                        sleep_ms(10);
                        break;
                    }
                    sleep_ms(10); 
                }
                           
                // for (i = 0; i < 100; i++){
                //     if(!gpio_get(BOOT_PIN)) {
                //         printf("1\n");
                //         set_neopixel_color(0X0000FF00);
                //     } 
                //     else {
                //         printf("0\n");
                //         set_neopixel_color(0x00000000);
                //     }
                //     sleep_ms(100);
                // }
                // printf("Finish the recording.\n");
                // set_neopixel_color(0X00000000);
                // sleep_ms(100);
                break;
                
            case 'p':
                while(true){
                    flag = 0x00000000;
                    flag = getchar_timeout_us(0);
                    if(flag == '1'){
                        set_neopixel_color(0X000000FF);
                    }
                    if(flag == '0'){
                        set_neopixel_color(0x00000000);
                    }
                    if(flag == 'N'){
                        set_neopixel_color(0x00000000);
                        sleep_ms(10);
                        break;
                    }
                    sleep_ms(10);
                }
                break;

        }
    }

    // printf("Now play the recording:\n");

    // for (i = 0; i < 100; i++)
    //     printf("%d ", array[i]);
    // printf("\n");
    
    // while(true){
    //     float speed = 1;
    //     printf("Enter the speed you want to speed up: \n");
    //     scanf("%f", &speed);
    //     printf("The speed now is x%f\n", speed);

    
    //     for (i = 0; i < 100; i++){
    //         if(array[i] == 1) {
    //             set_neopixel_color(0X000000FF);
    //             sleep_ms(100/speed);
    //         } else {
    //             set_neopixel_color(0x00000000);
    //             sleep_ms(100/speed);
    //         }
    //     }
        
    // sleep_ms(1000);
    // set_neopixel_color(0x00000000);
   
    // }
}
```

### Result:

The result is shown in [youtube video](https://youtu.be/-8h8KXTmqto). It is same as part 3 demo with speed up/down option included.
