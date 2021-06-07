#include <I2C_MPU6886.h>

#include "M5Atom.h"

//uint8_t FSM = 0;
unsigned long previousTime=0;
bool state=false;
int n=5;
float ax=0, ay=0, az=0;
float ax_avg=0, ay_avg=0, az_avg=0;
bool IMU6886Flag = false;


void setup()
{
   M5.begin(true, false, true);
       IMU6886Flag = M5.IMU.Init() == 0;
}


uint8_t FSM=-1;


void loop()
{
        switch (FSM)
        {

        case 0:
         {
          M5.dis.fillpix(0x000000);//black
          break;
          }

        case 1:
         {
              if(state==false){
                  M5.dis.fillpix(0x00ff00);//red
              }
              else if(state==true) {
                 M5.dis.fillpix(0x000000);//black
              }

            break;
        }


        case 2:
        {
            if(state==false){
                 M5.dis.fillpix(0xffffff);//white
              }
              else if(state==true){
                M5.dis.fillpix(0x000000);//black
              }

            break;
        }

       
        case 3:
          {
              if (IMU6886Flag)
              {
                  M5.IMU.getAccelData (&ax, &ax, &ax);
                 
                  ax_avg = ((ax * (n - 1)) + fabs(ax)) / n;
               //   ay_avg = ((ay * (n - 1)) + fabs(ay)) / n;
                 // az_avg = ((az * (n - 1)) + fabs(az)) / n;

                  if (abs (ax_avg)<0.8 )
                  {

                     
                       
                                if(state==false){
                                M5.dis.fillpix(0x00ff00);//red
                                }
                              else if(state==true)
                              {
                                   M5.dis.fillpix(0x000000);//black
                                }      
                               
                     
                    }
                   
                    else
                    {
     
                                  M5.dis.fillpix(0x00ff00);//red
                               
                   
                    }
                   
              }
                break;
          }
   

        case 4:
          {
              if (IMU6886Flag)
              {
                  M5.IMU.getAccelData (&ax, &ax, &ax);
                 
                  ax_avg = ((ax * (n - 1)) + fabs(ax)) / n;
               //   ay_avg = ((ay * (n - 1)) + fabs(ay)) / n;
                 // az_avg = ((az * (n - 1)) + fabs(az)) / n;

                  if (abs (ax_avg)<0.8 )
                  {
                                if(state==false){
                                M5.dis.fillpix(0xffffff);//red
                                }
                              else if(state==true)
                              {
                                   M5.dis.fillpix(0x000000);//black
                                }      
                    }
                   
                    else
                    {
     
                                  M5.dis.fillpix(0xffffff);//red
                           
                   
                    }
                   
              }
                break;
          }

         
        default:
            break;
        }

      //millis retrieves currentc time
     if(millis()-previousTime>=50){ //if 50 milliseconds passed, switch the state
            state=!state;
            previousTime=millis();
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
