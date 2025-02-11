
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "string.h"
#include "APDS9960.h"
#include "pio_i2c.h"



#define POWER_ENABLE 1
#define PROXIMITY_ENABLE 1
#define ALS_ENABLE 1
#define GESTURE_ENABLE 0

#define ALS_GAIN 0
#define ALS_TIME 219

#define INIT_CONFIG (GESTURE_ENABLE << 6u) | (PROXIMITY_ENABLE << 2u) | (ALS_ENABLE << 1u) | POWER_ENABLE

const int addr = 0x39;

#define PIN_SDA 22
#define PIN_SCL 23


PIO pio = pio0;
uint sm = 0;

void APDS9960_init() {
    // use the "handheld device dynamic" optimal setting (see datasheet)
    uint8_t buf[2];

    // send register number followed by its corresponding value
    buf[0] = ENABLE_REG;
    buf[1] = INIT_CONFIG;
    pio_i2c_write_blocking(pio, sm, addr, buf, 2, false);

    buf[0] = ALS_TIME_REG;
    buf[1] = ALS_TIME;
    pio_i2c_write_blocking(pio, sm, addr, buf, 2, false);
}

void read_proximity(int32_t* proximity) {

    uint8_t buf[1];
    uint8_t reg = PDATA_REG;
    pio_i2c_write_blocking(pio, sm, addr, &reg, 1, true);  // true to keep master control of bus
    pio_i2c_read_blocking(pio, sm, addr, buf, 1, false);  // false - finished with bus

    *proximity = buf[0];
}

void read_rgbc(int32_t* r, int32_t* g, int32_t* b, int32_t* c) {

    uint8_t buf[2];
    uint8_t c_addr = CDATA_REG_L;
    pio_i2c_write_blocking(pio, sm, addr, &c_addr, 1, true);  // true to keep master control of bus
    pio_i2c_read_blocking(pio, sm, addr, buf, 2, false);  // false - finished with bus
    // *c = buf[1]; 
    // *c = c* << 8;
    // *c|= buf[0];
    *c = buf[0] | (buf[1] << 8);
    
    uint8_t r_addr = RDATA_REG_L;
    pio_i2c_write_blocking(pio, sm, addr, &r_addr, 1, true); // true to keep master control of bus
    pio_i2c_read_blocking(pio, sm, addr, buf, 2, false);

    *r = buf[0] | (buf[1] << 8);

    uint8_t g_addr = GDATA_REG_L;
    pio_i2c_write_blocking(pio, sm, addr, &g_addr, 1, true); // true to keep master control of bus
    pio_i2c_read_blocking(pio, sm, addr, buf, 2, false);

    *g = buf[0] | (buf[1] << 8);

    uint8_t b_addr = BDATA_REG_L;
    pio_i2c_write_blocking(pio, sm, addr, &b_addr, 1, true); // true to keep master control of bus
    pio_i2c_read_blocking(pio, sm, addr, buf, 2, false);

    *b = buf[0] | (buf[1] << 8);
}

    
int main() {
    stdio_init_all();

    uint offset = pio_add_program(pio, &i2c_program);
    i2c_program_init(pio, sm, offset, PIN_SDA, PIN_SCL);
    sleep_ms(5000);
    APDS9960_init();

    while (true) {
        
        int32_t proximity;
        int32_t r,g,b,c;

        read_proximity(&proximity);
        read_rgbc(&r, &g, &b, &c);

        printf("proximity: %d   ",proximity);
        printf("r:%d, g:%d, b:%d, c:%d\n", r, g, b, c);

        sleep_ms(100);
        
    }
}