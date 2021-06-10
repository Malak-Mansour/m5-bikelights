# m5-bikelights

This code turns the M5Stack ATOM Matrix/ Lite into a bikelight iterating through 5 modes as the user chooses.

## M5 Stack ATOM Matrix/ Lite
This development board is based around the ESP32 PICO processor, has a programmable button, 5x5 RGB LED matrix panel(WS2812C),
Built-in Infra-red LED transmitter, Built-in MPU6886 Inertial Sensor, Extendable Pins & Holes, and can be programmed through the
Arduino Environment.


## Usage

| Mode  | ATOM Display | 
| ------------- | ------------- |
| OFF  | All LEDs off  |
| Manual Rear strobe (RED) | LEDs strobe at a predetermined interval |
| Manual Front strobe (WHITE) | LEDs strobe at a predetermined interval |
| Automatic Rear Mode Rear (RED) | LEDs are solid during a braking event. Return to strobe when riding |
| Automatic Front Mode Rear (WHITE) | LEDs are solid during a braking event. Return to strobe when riding |


Once the M5stack atom gets started, it displays the OFF mode.

With each time the user presses the ATOM screen, it moves to the next mode in the list. If the screen is pressed whilst on the 5th mode, it moves back to the 1st mode.

Once the button is pressed, the atom moves to the second mode, Manual Rear strobe (RED), which involves displaying a flashing/strobing red color.

Once the button is pressed again, the atom moves to the third mode, Manual Front strobe (WHITE), which involves displaying a flashing/strobing white color.

The next mode, which is also accessed upon pressing the button, Automatic Rear Mode Rear (RED), involves displaying a flashing/strobing red color when the atom is in inertia: moving at a steady speed or at rest.
When the atom brakes suddenly, a solid red color gets displayed for a very short period of time after which it goes back to strobing.

The 5th and last mode functions the exact same as the 5th one, except it displays white instead of red.

