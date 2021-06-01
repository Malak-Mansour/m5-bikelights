/*make use of: https://github.com/m5stack/M5Atom
   https://github.com/m5stack/m5-docs/blob/master/docs/en/api/lcd.md
  void drawpix(uint8_t xpos, uint8_t ypos, CRGB Color): Set the color of a LED in coordinate mode
  void displaybuff(uint8_t *buffptr, int8_t offsetx = 0, int8_t offsety = 0): Display an image
  https://github.com/lukasmaximus89/M5Atom-Resources/blob/master/glcdfont.c for font
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ); to get x,y,&z axis rotations
   M5.IMU.getAhrsData(&pitch, &roll, &yaw); to get attitude along all axes
*/

#include <I2C_MPU6886.h>

#include "M5Atom.h"

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>



#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif
#define PIN 27

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};




float t = 0, t_f = 0, t_k = 0; //temporary variable to store current temperatures
uint8_t FSM = -1;
unsigned long previousTime = 0;
bool state = false;
int n = 144; //array size, 24hrs  milliseconds
//float ax=0, ay=0, az=0;
//float ax_avg=0, ay_avg=0, az_avg=0;
bool IMU6886Flag = false;

//array to store temperature values from the last 24 hours (one value each 5 mins)
unsigned long temp24h[n] = 0;
int ctr = 0; //for array indeces
unsigned long sum = 0; //for sum of array elements
unsigned long avgTemp24 = 0;


void setup()
{
  Serial.begin(115200);
  M5.begin(true, true, true);
  M5.IMU.Init();

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
}


int x    = matrix.width();
int pass = 0;

void loop()
{
  switch (FSM)
  {

    case 0:
      {

        M5.IMU.getTempData(&t);
        
        //display t value + degree celsius beside it

        break;
      }

    case 1:
      {
        sum = 0;
        for (int i = 0; i < n; i++)
        {
          sum += temp24h[i];
        }
        avgTemp24 = sum / n;
        //display avgTemp24 value
        
        matrix.fillScreen(0);
        matrix.setCursor(x, 0);
        matrix.print(F(avgTemp24+"*C"));
        if (--x < -25) {
          x = matrix.width();
          if (++pass >= 4) pass = 0;
          matrix.setTextColor(colors[pass]);
        }

        break;
      }


  /*  case 2:
      {

        //for color range, use the same conditions for if else statements
        //but put all colors together on one screen

        if (t < 15)
          //display yellow
          else if (t >= 15 && t < 22)
            //display purple
            else if (t >= 22 && t < 35)
              //display blue
              else if (t >= 35 && t < 39)
                //display green
                else if (t >= 15 && t < 22)
                  //display red

                  break;
      }


    case 3:
      {
        //check function for graphing
        break;
      }


    case 4:
      {
        t_k = t + 273;
        //display t_k + the units K

        t_f = (t * (9 / 5)) + 32;
        //display t_f + the units degree F

        break;
      }*/


    default:
      break;
  }


  //millis retrieves currentc time
  //if 5 minutes passed, get the temp and store in array
  if (millis() - previousTime >= 5 * 60 * 1000) {
    M5.IMU.getTempData(&t);
    temp24h[ctr] = t;

    //only increment while array is not full yet
    if (ctr < n) {
      ctr++;
    }


    //once all are filled, shift each value in array 1 unit to the left
    if (ctr >= n) {

      for (int j = 0; j < 143; j++) {
        temp24h[j] = temp24h[j + 1];
      }

    }

  }


  if (M5.Btn.wasPressed())
  {
    FSM++;
    if (FSM >= 2)
    {
      FSM = 0; //so the counter resets and loops back to the beginning
    }
    // void clear();//to clear previous display and show the next one in the case
  }

  matrix.show();
  M5.update();
}
