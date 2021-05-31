/*make use of: https://github.com/m5stack/M5Atom
 *void drawpix(uint8_t xpos, uint8_t ypos, CRGB Color): Set the color of a LED in coordinate mode
 *void displaybuff(uint8_t *buffptr, int8_t offsetx = 0, int8_t offsety = 0): Display an image
 */

#include <I2C_MPU6886.h>

#include "M5Atom.h"

float t=0; //temporary variable to store current temperatures
uint8_t FSM=-1;
unsigned long previousTime=0;
bool state=false;
int n=144; //array size, 24hrs  milliseconds
//float ax=0, ay=0, az=0;
//float ax_avg=0, ay_avg=0, az_avg=0;
bool IMU6886Flag = false;

//array to store temperature values from the last 24 hours (one value each 5 mins)
unsigned long temp24h[n]=0;
int ctr=0; //for array indeces
unsigned long sum = 0; //for sum of array elements
unsigned long avgTemp24=0;


void setup()
{
  Serial.begin(115200);
  M5.begin(true, true, true);
  M5.IMU.Init();
}


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
            for (i=0; i< n; i++)
            {
                sum += array[i];
            }
            avgTemp24=sum/n;
            //display avgTemp24 value

            break;
        }


        case 2:
        {

          //for color range, use the same conditions for if else statements but put all colors together on one screen
           
            if(t<15)
              //display yellow
            else if (t>=15 && t<22)
              //display purple
            else if (t>=22 && t<35)
              //display blue
            else if (t>=35 && t<39)
              //display green
            else if (t>=15 && t<22)
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

             //display t + the units degree C

              t_k=t+273;
              //display t_k + the units K

              t_f=(t*(9/5))+32;
              //display t_f + the units degree F
              
                break;
          }

          
        default:
            break;
        }


      //millis retrieves currentc time
     if(millis()-previousTime>=5*60*1000){ //if 5 minutes passed, get the temp and store in array
            M5.IMU.getTempData(&t);
            temp24h[ctr]=t;

            if (ctr<n){ //only increment while array is not full yet
              ctr++;
            }


            if(ctr>=n){ //once all are filled, shift each value in array 1 unit to the left
              
              for(int j=0;j<143;j++){
                temp24h[j]=temp24h[j+1];
              }
              
            }
            
      }

   
    if (M5.Btn.wasPressed())
        {
            FSM++;
            if (FSM >= 5)
            {
                FSM = 0; //so the counter resets and loops back to the beginning
            }
        }


    M5.update();
}
