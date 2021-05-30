#include <I2C_MPU6886.h>
#include "M5Atom.h"
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
       
                  if (abs (ax_avg)<0.8 )
                  {
                       if(state==false)
                       {
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
