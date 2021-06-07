# m5-bikelights
 atom/arduino

 Functionalities and method of using the bikelights M5stack atom: 

Once the M5stack atom gets started, it displays the 1st mode, known as the 'Off' mode as all LEDs are off. 

Once the button is pressed, the atom moves to the second mode, Manual Rear strobe (RED), which involves displaying a flashing/strobing red color.

Once the button is pressed again, the atom moves to the third mode, Manual Front strobe (WHITE), which involves displaying a flashing/strobing white color.

The next mode, which is also accessed upon pressing the button, Automatic Rear Mode Rear (RED), involves displaying a flashing/strobing red color when the atom is in inertia: moving at a steady speed or at rest.
When the atom brakes suddenly, a solid red color gets displayed for a very short period of time after which it goes back to strobing.

The fifth and last mode functions the exact same as the previous one, except it displays white instead of red.

When the button is pressed again it goes back to the off mode and this sequence of modes keeping looping infinitely as long as the user presses on the screen to move between the modes sequentially. 