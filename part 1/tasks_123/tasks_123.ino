#include "M5Atom.h"

uint8_t FSM = 0;
unsigned long previousTime=0; 
bool state=false;


void setup()
{
   M5.begin(true, false, true);
}



void loop()
{
    //millis retrieves current time
     if(millis()-previousTime>=50){ //if 50 milliseconds passed, switch the state 
            state=!state;
            previousTime=currentTime;
     }

    
    if (M5.Btn.wasPressed())
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
                  M5.dis.fillpix(0x00ff00));//red
              }
              elseif(state==true) {
                 M5.dis.fillpix(0x000000);//black
              }
            
            break;
        }

         
        case 2:
        {
            if(state==false){
                 M5.dis.fillpix(0xffffff);//white
              }
              elseif(state==true){
                M5.dis.fillpix(0x000000);//black
              }
           
            break;
        }

 
        default:
            break;
        }

        FSM++;
        if (FSM >= 3)
        {
            FSM = 0;
        }
    }

    M5.update();
}
