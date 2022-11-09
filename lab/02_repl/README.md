### TODO:

Create a REPL to let you read and write RP2040 registers from a console. You should be able to:
- select any 32-bit address to read/write (even if not a valid RP2020 address)
- read/write any 32-bit value to this address
- read/write using any of the atomic bit-setting aliases and a 32-bit mask


### Introduction:

In this part, we will basically use RP2040. The ideal program should be that when the program starts, it will ask the user to select/input a register address then choose to read/write. Once it finished expected reading/writing, it will print a success message from the console.


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

}
```

### Result
Firstly we choose the address 0xd0000060, which can be read and edit with 0-31 bits. We first read the original value at the address (0x7fffff) and then modified it as 0x8fffff. The console shows that the value has been successfully edited.

<img width="812" alt="c0aa2e0613abe06ee8e52c8e7b7e364" src="https://user-images.githubusercontent.com/114200453/200707462-23939d56-df64-4e53-aca9-e10345946937.png">

Then we access the address 0xd0000004, the boot button. When we release the button, the read value is 0x200800 and the return value changed to 0x800 when we pressed the button.

![cd50704cb7af7efced7b3f73cd7a0e0](https://user-images.githubusercontent.com/114200453/200717032-e4f219ca-ec10-4f5c-82f4-684a87ea1b0d.png)




