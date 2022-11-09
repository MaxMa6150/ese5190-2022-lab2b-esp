### TODO:

Update your sequencer to be able to slow down and speed up recordings/replay. On the input side, the goal is ultimately to be able to handle the full 4 Gbps "firehose" from the PIO logic analyzer example in the SDK manual, which would fill up 256Kb of RAM in only 31 µs at a system clock speed of 125000 MHz if captured 'raw'! On the output side, the goal is to be able to output precisely timed sequences from the PIO at system clock resolution based on a handful of control points.

- update your sequencer to be able to record just the timestamped transitions between input values, and to be able to play data in this format
- give your sequencer the ability to select a range of output rates for both live and recorded input


### Code:

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
#define NUM_PIXELS 150

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else

// default to pin 2 if the board doesn't have a default WS2812 pin defined

#define WS2812_PIN 12
#define WS2812_POWER_PIN 11
#define MAX 100
#endif

int main() {
    stdio_init_all();

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    turn_on_power();
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    const uint BOOT_PIN = 21;
    // the BOOT button is GPIO21
    gpio_init(BOOT_PIN);
    gpio_set_dir(BOOT_PIN, GPIO_IN);

    int array[MAX]={0};
    int i;

    sleep_ms(10000);

    printf("Start the recording after red light:\n");
    set_neopixel_color(0X00FF0000);
    sleep_ms(1000);
    for (i = 0; i < 100; i++){
        if(!gpio_get(BOOT_PIN)) {
            array[i]=1;
            set_neopixel_color(0X0000FF00);
        } 
        else {
            array[i]=0;
            set_neopixel_color(0x00000000);
        }
        sleep_ms(100);
    }
    
            
    printf("Finish the recording.\n");
    set_neopixel_color(0X00000000);
    sleep_ms(100);
    printf("Now play the recording:\n");

    for (i = 0; i < 100; i++)
        printf("%d ", array[i]);
    printf("\n");
    
    while(true){
        float speed = 1;
        printf("Enter the speed you want to speed up: \n");
        scanf("%f", &speed);
        printf("The speed now is x%f\n", speed);

    
        for (i = 0; i < 100; i++){
            if(array[i] == 1) {
                set_neopixel_color(0X000000FF);
                sleep_ms(100/speed);
            } else {
                set_neopixel_color(0x00000000);
                sleep_ms(100/speed);
            }
        }
        
    sleep_ms(1000);
    set_neopixel_color(0x00000000);
   
    }
}
```
