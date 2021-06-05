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


/*WHITE = 0xffffff;
  BLACK = 0x000000;
  RED = 0x00ff00;
  ORANGE = 0x7bff00;
  YELLOW = 0xffff00;
  GREEN = 0xff0000;
  BLUE = 0x0000ff;*/

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
unsigned long sum2 = 0; //for sum of array elements
unsigned long avgTemp24 = 0;
int count2 = 0;
char tempCharArray[4];
//2 for main temp whole number, 1 for decimal point, 1 for number after decimal point
//array to store temp after float temp was converted to char array

float graphArray[24] = {0}; //create new array to store non-zero temp values

extern const unsigned char image_1[77];
extern const unsigned char image_2[77];
extern const unsigned char image_3[77];
extern const unsigned char image_4[77];
extern const unsigned char image_5[77];
extern const unsigned char image_6[77];
extern const unsigned char image_7[77];
extern const unsigned char image_8[77];
extern const unsigned char image_9[77];
extern const unsigned char image_0[77];
extern const unsigned char image_decimal[77];
extern const unsigned char image_Celsius [77]; //variable is declared with extern because of the definition in the c files
extern const unsigned char image_Fahrenheit [77];
extern const unsigned char image_Kelvin [77];


void setup()
{
  Serial.begin(115200);
  M5.begin(true, true, true);

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(15);

  IMU6886Flag = M5.IMU.Init() == 0;

}

int tempUnit = 1; //represents celsius


void displayTempOnMatrix(char *tempCharArray, int tempUnit)
{
  for (int i = 0; i < 5; i++) //5 loops because we want temp in celsius to 2 decimal places, and 1 decimal places in kelvin/fahrenheit
  {

    if (tempCharArray[i] == '.')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_decimal, 0, 0); //Display image of decimal point
      //M5.dis.animation((uint8_t *)image_decimal, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("decimal");
    }
    else if (tempCharArray[i] == '0')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_0, 0, 0); //Display image 0
      //M5.dis.animation((uint8_t *)image_0, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("0");
    }
    else if (tempCharArray[i] == '1')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_1, 0, 0); //Display image 1
      //M5.dis.animation((uint8_t *)image_1, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("1");
    }
    else if (tempCharArray[i] == '2')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_2, 0, 0); //Display image 2
      //M5.dis.animation((uint8_t *)image_2, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("2");
    }
    else if (tempCharArray[i] == '3')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_3, 0, 0); //Display image 3
      //M5.dis.animation((uint8_t *)image_3, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("3");
    }
    else if (tempCharArray[i] == '4')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_4, 0, 0); //Display image 4
      //M5.dis.animation((uint8_t *)image_4, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("4");
    }
    else if (tempCharArray[i] == '5')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_5, 0, 0); //Display image 5
      //M5.dis.animation((uint8_t *)image_5, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("5");
    }
    else if (tempCharArray[i] == '6')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_6, 0, 0); //Display image 6
      //M5.dis.animation((uint8_t *)image_6, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("6");
    }
    else if (tempCharArray[i] == '7')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_7, 0, 0); //Display image 7
      //M5.dis.animation((uint8_t *)image_7, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("7");
    }
    else if (tempCharArray[i] == '8')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_8, 0, 0); //Display image 8
      //M5.dis.animation((uint8_t *)image_8, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("8");
    }
    else if (tempCharArray[i] == '9')
    {
      M5.dis.clear();
      M5.dis.displaybuff((uint8_t *)image_9, 0, 0); //Display image 9
      //M5.dis.animation((uint8_t *)image_9, 2 , 1, -1);
      do {

      } while (millis() - previousTime < 500);
      previousTime = millis();
      Serial.printf("9");
    }

  }

  if (tempUnit == 1) {
    M5.dis.clear();
    M5.dis.displaybuff((uint8_t *)image_Celsius, 0, 0); //Display image for Celsius
    do {

    } while (millis() - previousTime < 500);
    previousTime = millis();    Serial.println("degrees celsius");
  }
  else if (tempUnit == 2) {
    M5.dis.clear();
    M5.dis.displaybuff((uint8_t *)image_Fahrenheit, 0, 0); //Display image for Fahrenheit
    do {

    } while (millis() - previousTime < 500);
    previousTime = millis();    Serial.println("degrees fahrenheit");

  }
  else if (tempUnit == 3) {
    M5.dis.clear();
    M5.dis.displaybuff((uint8_t *)image_Kelvin, 0, 0); //Display image for Kelvin
    do {

    } while (millis() - previousTime < 500);
    previousTime = millis();    Serial.println("kelvin");

  }


  M5.dis.clear();
  do {

  } while (millis() - previousTime < 500);
  previousTime = millis();
}


void graphColorScale(float *graphArray) {

  M5.dis.drawpix(0, 0xffffff); //white
  Serial.println("white");

  for (int i = 0; i < 24; i++) {

    if (graphArray[i] == 0)
    { M5.dis.drawpix((i + 1), 0x000000); //black, meaning data was not collected for that array number yet
      Serial.println("black");
    }
    else if (graphArray[i] < 15 && graphArray[i] != 0)
    { M5.dis.drawpix((i + 1), 0x0000ff); //blue
      Serial.println("blue");
    }
    else if (graphArray[i] >= 15 && graphArray[i] < 22)
    { M5.dis.drawpix((i + 1), 0xff0000); //green
      Serial.println("green");
    }
    else if (graphArray[i] >= 22 && graphArray[i] < 35)
    { M5.dis.drawpix((i + 1), 0xffff00); //yellow
      Serial.println("yellow");
    }
    else if (graphArray[i] >= 35 && graphArray[i] < 39)
    { M5.dis.drawpix((i + 1), 0x7bff00); //orange
      Serial.println("orange");
    }
    else if (graphArray[i] >= 39)
    { M5.dis.drawpix((i + 1), 0x00ff00); //red
      Serial.println("red");
    }
  }
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

    previousTime = millis();

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



  if (accX > 0.5) { //titled to the right
    if (state == false) {
      FSM++;
      state = true;
    }
    if (FSM > 5) FSM = 1;
  }

  else if (accX < -0.5) { //titled to the left
    if (state == false) {
      FSM--;
      state = true;
    }
    if (FSM < 1) FSM = 5;
  }

  if (accX < 0.5 && accX > -0.5) {
    state = false;
  }

  if (accZ > 0.5) { //facing down, nothing displayed
    FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets back to 0
  }


  switch (FSM)
  {

    case 0: //off (sleeping mode)
      {
        M5.dis.fillpix(0x000000);//black
        Serial.println("black_0");

        if (accZ < 0.5 && accZ > -0.5 && M5.Btn.wasReleased()) { //activation/waking up conditions
          FSM++;
        }
        break;
      }

    case 1: //display current temp
      {
        if (accZ > 0.5) {

          FSM = 0;  //facing down, nothing displayed
          Serial.println("black_1");
        }

        else {
          M5.dis.clear();
          M5.dis.displaybuff((uint8_t *)image_1, 0, 0); //Display image 1
          do { } while (millis() - previousTime < 1000);
          previousTime = millis();
          Serial.println("image 1");

          if (M5.Btn.wasReleased()) {
            M5.IMU.getTempData(&t);
            Serial.println("got temp");
            dtostrf(t, 5, 2, tempCharArray); //creates char array of size 4 and 1 decimal place from float temperature
            Serial.println("got tempCharArray array");

            displayTempOnMatrix(tempCharArray, 1);
            Serial.println("displayed on matrix");
          }
        }
        break;
      }

    case 2: //calculate avg temp
    { if (accZ > 0.5) { //facing down, nothing displayed
          FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets everything back to 0
        }

        else {
          M5.dis.clear();
          M5.dis.displaybuff((uint8_t *)image_2, 0, 0); //Display image 2
          do { } while (millis() - previousTime < 1000);
          previousTime = millis();
          Serial.println("image 2");


          if (M5.Btn.wasReleased())
          {
            sum2 = 0;
            count2 = 0;

            for (int i = 0; i < n; i++)
            {
              if (temp24h[i] != 0) {
                sum2 += temp24h[i];
                count2++;
              }
            }

            if (sum2 == 0 && count2 == 0) {
              M5.IMU.getTempData(&t);

              avgTemp24 = t;
            }
            else {
              avgTemp24 = sum2 / count2;
            }



            dtostrf(avgTemp24, 5, 2, tempCharArray); //creates char array of size 4 and 1 decimal place from float temperature
            Serial.println("got tempCharArray array");

            displayTempOnMatrix(tempCharArray, 1);
            Serial.println("displayed on matrix");

            Serial.println("avgTemp24 displayed");
          }
        }
        break;
      }


    case 3: //color scale
    { if (accZ > 0.5) { //facing down, nothing displayed
          FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets everything back to 0
        }

        else {
          M5.dis.clear();
          M5.dis.displaybuff((uint8_t *)image_3, 0, 0); //Display image 3
          do { } while (millis() - previousTime < 1000);
          previousTime = millis();
          Serial.println("image 3");

          if (M5.Btn.wasReleased())
          {
            //blue
            M5.dis.drawpix(0, 0x0000ff);
            M5.dis.drawpix(5, 0x0000ff);
            //green
            M5.dis.drawpix(1, 0xff0000);
            M5.dis.drawpix(6, 0xff0000);
            //yellow
            M5.dis.drawpix(2, 0xffff00);
            M5.dis.drawpix(7, 0xffff00);
            //orange
            M5.dis.drawpix(3, 0x7bff00);
            M5.dis.drawpix(8, 0x7bff00);
            //red
            M5.dis.drawpix(4, 0x00ff00);
            M5.dis.drawpix(9, 0x00ff00);

            M5.IMU.getTempData(&t);


            if (t < 15) {   //display blue
              M5.dis.drawpix(11, 0x0000ff); M5.dis.drawpix(12, 0x0000ff); M5.dis.drawpix(13, 0x0000ff); M5.dis.drawpix(14, 0x0000ff); M5.dis.drawpix(15, 0x0000ff);
              M5.dis.drawpix(16, 0x0000ff); M5.dis.drawpix(17, 0x0000ff); M5.dis.drawpix(18, 0x0000ff); M5.dis.drawpix(19, 0x0000ff); M5.dis.drawpix(20, 0x0000ff);
              M5.dis.drawpix(21, 0x0000ff); M5.dis.drawpix(22, 0x0000ff); M5.dis.drawpix(23, 0x0000ff); M5.dis.drawpix(24, 0x0000ff); M5.dis.drawpix(10, 0x0000ff);
            }

            else if (t >= 15 && t < 22) //display green
            {
              M5.dis.drawpix(11, 0xff0000); M5.dis.drawpix(12, 0xff0000); M5.dis.drawpix(13, 0xff0000); M5.dis.drawpix(14, 0xff0000); M5.dis.drawpix(15, 0xff0000);
              M5.dis.drawpix(16, 0xff0000); M5.dis.drawpix(17, 0xff0000); M5.dis.drawpix(18, 0xff0000); M5.dis.drawpix(19, 0xff0000); M5.dis.drawpix(20, 0xff0000);
              M5.dis.drawpix(21, 0xff0000); M5.dis.drawpix(22, 0xff0000); M5.dis.drawpix(23, 0xff0000); M5.dis.drawpix(24, 0xff0000); M5.dis.drawpix(10, 0xff0000);
            }
            else if (t >= 22 && t < 35) //display yellow
            {
              M5.dis.drawpix(11, 0xffff00); M5.dis.drawpix(12, 0xffff00); M5.dis.drawpix(13, 0xffff00); M5.dis.drawpix(14, 0xffff00); M5.dis.drawpix(15, 0xffff00);
              M5.dis.drawpix(16, 0xffff00); M5.dis.drawpix(17, 0xffff00); M5.dis.drawpix(18, 0xffff00); M5.dis.drawpix(19, 0xffff00); M5.dis.drawpix(20, 0xffff00);
              M5.dis.drawpix(21, 0xffff00); M5.dis.drawpix(22, 0xffff00); M5.dis.drawpix(23, 0xffff00); M5.dis.drawpix(24, 0xffff00); M5.dis.drawpix(10, 0xffff00);
            }
            else if (t >= 35 && t < 39) //display orange
            {
              M5.dis.drawpix(11, 0x7bff00); M5.dis.drawpix(12, 0x7bff00); M5.dis.drawpix(13, 0x7bff00); M5.dis.drawpix(14, 0x7bff00); M5.dis.drawpix(15, 0x7bff00);
              M5.dis.drawpix(16, 0x7bff00); M5.dis.drawpix(17, 0x7bff00); M5.dis.drawpix(18, 0x7bff00); M5.dis.drawpix(19, 0x7bff00); M5.dis.drawpix(20, 0x7bff00);
              M5.dis.drawpix(21, 0x7bff00); M5.dis.drawpix(22, 0x7bff00); M5.dis.drawpix(23, 0x7bff00); M5.dis.drawpix(24, 0x7bff00); M5.dis.drawpix(10, 0x7bff00);
            }
            else if (t >= 39) //display red
            {
              M5.dis.drawpix(11, 0x00ff00); M5.dis.drawpix(12, 0x00ff00); M5.dis.drawpix(13, 0x00ff00); M5.dis.drawpix(14, 0x00ff00); M5.dis.drawpix(15, 0x00ff00);
              M5.dis.drawpix(16, 0x00ff00); M5.dis.drawpix(17, 0x00ff00); M5.dis.drawpix(18, 0x00ff00); M5.dis.drawpix(19, 0x00ff00); M5.dis.drawpix(20, 0x00ff00);
              M5.dis.drawpix(21, 0x00ff00); M5.dis.drawpix(22, 0x00ff00); M5.dis.drawpix(23, 0x00ff00); M5.dis.drawpix(24, 0x00ff00); M5.dis.drawpix(10, 0x00ff00);
            }

            do { } while (millis() - previousTime < 4000);
            previousTime = millis();
          }
        }
        break;
      }


    case 4: //graphing (elements in array temp24h over count
    { if (accZ > 0.5) { //facing down, nothing displayed
          FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets everything back to 0
        }
        else {
          M5.dis.clear();
          M5.dis.displaybuff((uint8_t *)image_4, 0, 0); //Display image 4
          do { } while (millis() - previousTime < 1000);
          previousTime = millis();
          Serial.println("image 4");

          if (M5.Btn.wasReleased())
          {
            //288 elements in temp24h,each element represents temp at the end of 5 mins, if we wanna graph the temp at the end of each hour, 288/24 = 12 , so we want every 12th element
            for (int i = 0; i < 24; i ++)
            {
              graphArray[i] = temp24h[(i * 12) + 11]; //we want 11th, 23rd, 35th (12th multiple-1), so using i, i*12+11 will get those values
              //or better, add to graphArray the average temperatures for each hour of the 24 hours
            }

            //display color representing each temperature per 24hrs using color scale
            graphColorScale(graphArray);

            Serial.println("graph");
            do { } while (millis() - previousTime < 4000);
            previousTime = millis();
          }
        }
        break;

      }


    case 5: //change units
    { if (accZ > 0.5) { //facing down, nothing displayed
          FSM = 0; //placed it here so that if titlting was detected but it was facing down, it resets everything back to 0
        }
        else {
          M5.dis.clear();
          M5.dis.displaybuff((uint8_t *)image_5, 0, 0); //Display image 5
          do { } while (millis() - previousTime < 1000);
          previousTime = millis();
          Serial.println("image 5");

          if (M5.Btn.wasReleased())
          {
            M5.IMU.getTempData(&t);


            t_f = (t * ((float(9)) / (float(5)))) + 32;
            dtostrf(t_f, 5, 2, tempCharArray);
            displayTempOnMatrix(tempCharArray, 2);
            Serial.println("t_f");


            M5.dis.clear();
            do {          } while (millis() - previousTime < 500);
            previousTime = millis();


            t_k = t + 273;
            dtostrf(t_k, 4, 1, tempCharArray);
            displayTempOnMatrix(tempCharArray, 3);
            Serial.println("t_k");

          }
        }
        break;
      }


    default:
      break;
  }

  M5.update();
}
