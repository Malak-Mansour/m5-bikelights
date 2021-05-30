#include "M5Atom.h"

uint8_t FSM = 0;
unsigned long previousTime=0; 
bool state=false;
int n;
float ax, ay, az;
float ax_avg, ay_avg, az_avg;


void setup()
{
   M5.begin(true, false, true);
}



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
            ax, ay, az = 0;
            ax_avg, ay_avg, az_avg = 0;
           
            M5.IMU.getAccel(&ax, &ay, &az);
            n = sizeof(ax);
            ax_avg = ax/n;
            ay_avg = ay/n;
            az_avg = az/n;
            //now calculate the moving average
            ax_avg = ((ax_avg * (n - 1)) + fabs(ax)) / n;
            ay_avg = ((ay_avg * (n - 1)) + fabs(ay)) / n;
            az_avg = ((az_avg * (n - 1)) + fabs(az)) / n;

            if (ax_avg>=thresh || ay_avg>=thresh || az_avg>=thresh)
            {
               while (FSM==3)
                   {
                        if(state==false){
                             M5.dis.fillpix(0x00ff00);//red
                          }
                        else if(state==true) {
                             M5.dis.fillpix(0x000000);//black
                          }
                   }
              }
              
              else
              {
                 M5.dis.fillpix(0x00ff00); // set state of color to solid red
              }

              break;
          }


          case 4:
          {
            ax, ay, az = 0;
            ax_avg, ay_avg, az_avg = 0;
           
            M5.IMU.getAccel(&ax, &ay, &az);
            n = sizeof(ax);
            ax_avg = ax/n;
            ay_avg = ay/n;
            az_avg = az/n;
            //now calculate the moving average
            ax_avg = ((ax_avg * (n - 1)) + fabs(ax)) / n;
            ay_avg = ((ay_avg * (n - 1)) + fabs(ay)) / n;
            az_avg = ((az_avg * (n - 1)) + fabs(az)) / n;

            if (ax_avg>=thresh || ay_avg>=thresh || az_avg>=thresh)
            {
               while (FSM==4)
                   {
                        if(state==false){
                             M5.dis.fillpix(0xffffff);//white
                          }
                        else if(state==true) {
                             M5.dis.fillpix(0x000000);//black
                          }
                   }
              }
              
              else
              {
                 M5.dis.fillpix(0xffffff); // set state of color to solid white
              }

              break;
          }
          
 
        default:
            break;
        }

//millis retrieves current time
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
