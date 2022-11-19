### TODO:

Use the capabilities of your sequencer to implement the ADPS9960 protocol and control the sensor.

### Intro:

In this part, the values of RGBC and proximity are read from APDS9960 via PIO I2C, and it will be displayed the collection of data on console.

### Note:

**Inspired by Dang0V, we need to edit pio_i2c.c and i2c.pio to read data:**

In pio_i2c.c file (line 89-110):

Firstly, we need to add an input variable `bool nostop`
```
int pio_i2c_write_blocking(PIO pio, uint sm, uint8_t addr, uint8_t *txbuf, uint len, bool nostop)
```

Then when we call function in read_proximity() and read_rgbc(), we set `nostop = true` and set `nostop = false` in function APDS_init()

Then in line 101 - 102:

```
if (!nostop)
   pio_i2c_stop(pio, sm);
```

Also, in i2c.pio, we need to add one line in line 62:
```
mov isr, null              ; Reset the input bit counter
```
After adding this line, we can correctly get proximity readout.

### Result

The console can print out the proximity and color change.

The result is shown in [youtube video].
