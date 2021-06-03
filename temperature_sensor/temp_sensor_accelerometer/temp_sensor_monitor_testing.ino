/*make use of: https://github.com/m5stack/M5Atom
   https://github.com/m5stack/m5-docs/blob/master/docs/en/api/lcd.md
  void drawpix(uint8_t xpos, uint8_t ypos, CRGB Color): Set the color of a LED in coordinate mode
  void displaybuff(uint8_t *1.c, int8_t offsetx = 0, int8_t offsety = 0): Display an image
  https://github.com/lukasmaximus89/M5Atom-Resources/blob/master/glcdfont.c for font
  M5.IMU.getAccelData(&accX, &accY, &accZ); to get x,y,&z axis rotations
   M5.IMU.getAhrsData(&pitch, &roll, &yaw); to get attitude along all axes
  // void displaybuff(uint8_t * 1.c, int8_t offsetx = 0, int8_t offsety = 0)

  M5.dis.displaybuff((uint8_t *)image_1, 0, 0); : Display an image
  M5.dis.animation((uint8_t *)image_1, amspeed, ammode, amcount = -1)
*/

#include <I2C_MPU6886.h>

#include "M5Atom.h"

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <stdlib.h>



#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif
#define PIN 27

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) //WHAT FOR??
};


float t = 0, t_f = 0, t_k = 0; //temporary variable to store current temperatures
uint8_t FSM = 0;
unsigned long previousTime = 0;
bool state = false;
int n = 288; //array size, (24hrs*60mins)/5mins: our predetermined interval
float accX = 0, accY = 0, accZ = 0;
bool IMU6886Flag = false;

//array to store temperature values from the last 24 hours (one value each 5 mins)
unsigned long temp24h[288] = {0};
int ctr = 0; //for array indeces
unsigned long sum = 0; //for sum of array elements
unsigned long avgTemp24 = 0;
int count = 0;
char charCelsius[4];

void setup()
{
  Serial.begin(115200);
  M5.begin(true, true, true);

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(15);
  matrix.setTextColor(colors[0]);

  IMU6886Flag = M5.IMU.Init() == 0;

}



void loop()
{

  M5.IMU.getTempData(&t);


  M5.IMU.getAccelData(&accX, &accY, &accZ);


  //millis retrieves currentc time
  //if 5 minutes passed, get the temp and store in array
  if (millis() - previousTime >= 5 * 60 * 1000) {
    M5.IMU.getTempData(&t);
    temp24h[ctr] = t;

    //only increment while array is not full yet
    if (ctr < (n - 1)) {
      ctr++;
    }

    //once all are filled, shift each value in array 1 unit to the left
    else if (ctr >= (n - 1)) {

      for (int j = 0; j < (n - 1); j++) {
        temp24h[j] = temp24h[j + 1];
      }

    }
  }



  if (accX > 0) { //titled to the right
    FSM++;
    if (FSM > 5) FSM == 1;
  }

  else if (accX < 0) { //titled to the left
    FSM--;
    if (FSM < 1) FSM == 5;
  }

  if (accZ > 0) { //facing down, nothing displayed
    FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets back to 0
  }


  switch (FSM)
  {

    case 0: //off (sleeping mode)
      {
        M5.dis.fillpix(0x000000);//black
        Serial.println("black_0");

        break;
      }

    case 1: //display current temp
    { if (accZ > 0) {
          FSM = 0;  //facing down, nothing displayed
          Serial.println("black_1");
        }

        else {
          M5.dis.displaybuff((uint8_t *)image_1, 0, 0); //Display image 1
          M5.dis.animation((uint8_t *)image_1, 2 , 1, -1)
          Serial.println("image 1");

          if (M5.Btn.wasPressed())
          {
            M5.IMU.getTempData(&t);

            String temp_C_string = dtostrf(t, 4, 1, charCelsius); //creates char array of size 4 and 1 decimal place from float temperature

            Serial.println(temp_C_string);
            matrix.printf(temp_C_string);

            if (millis() - previousTime >= 50) {
              M5.dis.displaybuff((uint8_t *)image_Celsius, 0, 0); //Display dgree sign
              M5.dis.animation((uint8_t *)image_Celsius, 2 , 1, -1); //NECESSARY?
            }

            
          }
        }
        break;
      }

    case 2: //calculate avg temp
    { if (accZ > 0) { //facing down, nothing displayed
          FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets everything back to 0
          break; //AS IN BREAK OUT OF THIS CASE, IDK IF ITS PLACED RIGHT THO
        }
        //display image 2
        Serial.println("image 2");


        if (M5.Btn.wasPressed())
        {
          sum = 0;
          count = 0;

          for (int i = 0; i < n; i++)
          {
            if (temp24h[i] != 0) {
              sum += temp24h[i];
              count++;
            }
          }

          avgTemp24 = sum / count;
          Serial.println(avgTemp24);

          //display avgTemp24
          //ALTERNATIVELY REPLACE *C WITH IMAGE I MADE!!
        }
        break;
      }


    case 3: //color scale
    { if (accZ > 0) { //facing down, nothing displayed
          FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets everything back to 0
          break; //AS IN BREAK OUT OF THIS CASE, IDK IF ITS PLACED RIGHT THO
        }
        //display image 3
        Serial.println("image 3");

        if (M5.Btn.wasPressed())
        {

          if (t < 15)
          { M5.dis.fillpix(0x0000ff);//blue
            Serial.println("blue");
          }
          else if (t >= 15 && t < 22)
          { M5.dis.fillpix(0x00ff00);//green
            Serial.println("green");
          }
          else if (t >= 22 && t < 35)
          { M5.dis.fillpix(0xf1c40f);//yellow
            Serial.println("yellow");
          }
          else if (t >= 35 && t < 39)
          { M5.dis.fillpix(0xd35400);//orange
            Serial.println("orange");
          }
          else if (t >= 15 && t < 22)
          { M5.dis.fillpix(0xff0000);//red
            Serial.println("red");
          }


          //color scale
          //blue
          M5.dis.drawpix(1, 0x0000ff);
          M5.dis.drawpix(6, 0x0000ff);
          Serial.println("blue");

          //green
          M5.dis.drawpix(2, 0x00ff00);
          M5.dis.drawpix(7, 0x00ff00);
          Serial.println("green");

          //yellow
          M5.dis.drawpix(3, 0xf1c40f);
          M5.dis.drawpix(8, 0xf1c40f);
          Serial.println("yellow");

          //orange
          M5.dis.drawpix(4, 0xd35400);
          M5.dis.drawpix(9, 0xd35400);
          Serial.println("orange");

          //red
          M5.dis.drawpix(5, 0xff0000);
          M5.dis.drawpix(10, 0xff0000);
          Serial.println("red");



        }
        break;
      }


    case 4: //graphing
    { if (accZ > 0) { //facing down, nothing displayed
          FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets everything back to 0
          break; //AS IN BREAK OUT OF THIS CASE, IDK IF ITS PLACED RIGHT THO
        }
        //display image 4
        Serial.println("image 4");

        if (M5.Btn.wasPressed())
        {
          //check function for graphing
          Serial.println("graph");

        }
        break;

      }


    case 5: //change units
    { if (accZ > 0) { //facing down, nothing displayed
          FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets everything back to 0
          break; //AS IN BREAK OUT OF THIS CASE, IDK IF ITS PLACED RIGHT THO
        }
        //display image 5
        Serial.println("image 5");

        if (M5.Btn.wasPressed())
        {
          M5.IMU.getTempData(&t);

          t_k = t + 273;
          //display t_k
          //ALTERNATIVELY REPLACE K WITH IMAGE I MADE!!
          Serial.println("t_k");


          t_f = (t * (9 / 5)) + 32;
          //display t_f
          //ALTERNATIVELY REPLACE *F WITH IMAGE I MADE!!
          Serial.println("t_f");

        }
        break;
      }


    default:
      break;
  }


  matrix.show();

  M5.update();
}
}
