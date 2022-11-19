### TODO:

Add support for your custom circuit board to your sequencer, and give a demo.
    
# Proposal

## Breadboard LED Buildup and RP2040 GPIO Test

In this part, we firstly try to build a single LED circuit (Blue LED and 1k protect resistor), then use GPIO pin on RP2040 as a power supply to drive the circuit.

We use GPIO pin at on the Stemma QT cable as the input, with the number "GPIO22"

The test code is shown below:

```
#include "pico/stdlib.h"

int main() {
    //const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    const uint LED_PIN = 22;      # since we use GPIO22 pin on Stemma QT, we initialize LED pin value as 22
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);    
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}
```
## Result

The result is shown below:

![](https://github.com/MaxMa6150/LAB2B_Proposal/blob/main/LED.gif)


# Outline

In lab 2B we plan to build the circuit in the following steps:

1) Since there are several GPIO pins on QT-PY 2040 which can be used as I/O ports. We plan to use several GPIO pins to drive several different color LEDs to connect in parallel (Or let's say we will build several individual LED circuits powered by different GPIO ports.) To test if those GPIO ports can drive different color LEDs individually, we can design different patterns similar to patterns in lab2A ws2812 example to light up LEDs (random, one-by-one, etc.)

2) Then, to make our design has some practical usage, we can utilize the sensor APDS9960, such as brightness detecting or gesture modules to control the change in LEDs. For example, if the sensor detects that the environment brightness is in a specific range, QT-PY 2040 will turn on one of the LEDs. Or if the sensor detects the continuing change in brightness, the circuit will light up one specific LED to show if the brightness is going up/down. We can design a program for the gesture sensor that uses different gestures to light up different color LEDs.

I think our design is cool because it integrates different devices we used in previous labs and makes designs with practical usage. For example, it can be used as a visualized brightness detector, or it can be used as a motion detector.

The components we will use in this lab are QT-PY 2040 and sensor APDS9960, which we have already gotten from lab 1. Besides, we will use resistors (330ohm - 1k ohm) and different color LEDs. All these items are available in Detkin Lab.

## Questions
For our design, we do have some questions:

1) When the sensor detects the brightness, will it return a specific value to RP2040? Or will it return values in a different pattern?

2) Same question for gesture sensor and its return... Will it use the I2C protocol?

*Since I tested positive, Ying and Sudong worked seperately with me. I worked on coding part and tested on breadboard. Ying and Sudong finished soildering process and tested on prototype board*

## Oct. 28th Uptading (Done by Ying and Sudong)

### Soldering Process

Since we had not finalized the proposal, we first solder QT PY 2040 on the prototype board.

![](https://github.com/MaxMa6150/LAB2B_Proposal/blob/main/soildering.gif)

### Soldering test

To test if the prototype works, we used the previous blinking code to test the board.

![](https://github.com/MaxMa6150/LAB2B_Proposal/blob/main/soildering%20test.gif)

## Nov. 3rd Uptading

### Planning, Coding and Breadboard Testing

We finally decided to work on our first plan in the outline above: using three LEDs in parallel which seperately connected with resistors in series as a traffic light. The lighting sequence will be: the loop would be: red on for 3s, then yellow blinks for 1s, then green on for 3s.

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
```
The result is shown below:

![](https://github.com/MaxMa6150/LAB2B_Proposal/blob/main/breadboard_test.gif)

When the red LED is on, the screen will show "Wait!" until green light is on with "Ready to go!" shown on screen.

After confirming the circuit and code work, we soldered it on the prototype board.

### Show Case

![927520edabd285b5f17250b07c2cb319 (2)](https://user-images.githubusercontent.com/113209201/199844649-651d14af-3e6d-44d9-bd40-b041eabe2921.gif)
