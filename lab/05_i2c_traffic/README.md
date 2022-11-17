### TODO:

- use your Lab 1 firefly code to generate ADPS9960 I2C traffic and display it on a lab oscilloscope
- take a screenshot of some portion of this exchange, and figure out/annotate what's happening based on the protocol documentation in the ADPS9960 datasheet 

### Introduction

In this part, we will use brightness sensor on APDS9960 connected with RP2040 via I2C and lab1 firefly code to measure SCL and SDK value through oscilloscope. The scope trace will show the I2C bus between RP2040 and APDS9960.
![2e5762c9d4801c056d7840178223c31](https://user-images.githubusercontent.com/114200453/202347142-775cb4ea-bf16-4d05-8fd9-39e6acbc1f6d.jpg)


### code

From lab1 firefly

```
#section3
import board
import busio
import adafruit_apds9960.apds9960
import time
import neopixel
import digitalio
import usb_hid
import analogio
from adafruit_hid.mouse import Mouse
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keyboard_layout_us import KeyboardLayoutUS
from adafruit_hid.keycode import Keycode
from adafruit_hid.mouse import Mouse

i2c = busio.I2C(board.SCL1, board.SDA1)
sensor = adafruit_apds9960.apds9960.APDS9960(i2c)
sensor.enable_proximity = True
sensor.enable_color = True
pixels = neopixel.NeoPixel(board.NEOPIXEL, 1)
clast=0
while True:
    r, g, b, c = sensor.color_data
    print(c)
    
    if c > (clast+100):
        pixels.fill((255, 255, 255))
        
    if c < (clast-100):
        pixels.fill((255, 255, 255))
        
    else:
        pixels.fill((0, 0, 0))
        
    clast=c
    time.sleep(0.01)
```
# SCL and SDA Screenshot
*since I tested positive, I did not attend to the lab today. The screenshots below are from Sudong and Ying's labwork.*

![40a3474c9e474f5d9529dda273621b4](https://user-images.githubusercontent.com/113209201/200035929-452c6688-bd88-4adc-8177-fd4764c10a40.jpg)

The yellow channel indicate Clock(SCL) readout and the green channel indicate data (SDK). They connected black cable to gnd pins on RP2040 and red pins to SCL and SDK seperately.

![image](https://user-images.githubusercontent.com/113209201/200041246-9d882efe-0237-468e-b7c9-95b1db2d0bdd.png)

From the graph we can see that the device is working in periods, now we zoom in to see periodic pattern and how two channel change with the change in brightness.

![62213fd31571ab3ffe3aeb3fabc07ac](https://user-images.githubusercontent.com/113209201/200036371-9c0d52a1-e57c-4ddd-982c-1cbd777e8709.jpg)

It is clear that each period have four data set in series and they have repeated pattern. Then we change the brightness (from dark to bright/from bright to dark) to see voltage output changes.

When detecting the increasingly low light source, the last several digits are low voltage outputs.

![3d5c23a98ebdacd54f04e88c1b5af01](https://user-images.githubusercontent.com/113209201/200036690-da966c74-9d4e-41c2-bfdc-072c24bd86bf.jpg)

When detecting the increasingly high light source, the last several digits are high voltage outputs.

![f6465ac69b59d430fef3c56bbb313d9](https://user-images.githubusercontent.com/113209201/200037348-f603d39a-9ff0-465d-aee1-571941d56c95.jpg)

