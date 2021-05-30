#include "M5Atom.h"

uint8_t DisBuff[2 + 5 * 5 * 3];
uint8_t FSM = 0;
unsigned long previousTime=0; 
bool state=false;
unsigned long currentTime;

void setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
    DisBuff[0] = 0x05;
    DisBuff[1] = 0x05;
    for (int i = 0; i < 25; i++)
    {
        DisBuff[2 + i * 3 + 0] = Rdata;
        DisBuff[2 + i * 3 + 1] = Gdata;
        DisBuff[2 + i * 3 + 2] = Bdata;
    }
}


void setup()
{
    M5.begin(true, false, true);
   setBuff(0x00, 0x00, 0x00);
   M5.dis.displaybuff(DisBuff);
   //M5.dis.drawpix(i,0x000000);//black
}



void loop()
{
    currentTime=millis(); //millis retrieves current time and stores it into variable currentTime
     if(currentTime-previousTime>=1000){ //if 1 second passed, switch the state 
            state=!state;
            previousTime=currentTime;
     }

    
    if (M5.Btn.wasPressed())
    {

        switch (FSM)
        {

        case 0:
         {         
         // M5.dis.drawpix(i,0x000000); //BLACK
          break;
          }
         
        case 1:        
         {
              if(state==false){
               // M5.dis.drawpix(i,0x00ff00); //red
                setBuff(0xff, 0x00, 0x00); //red
              }
              else {
              //  M5.dis.drawpix(i,0x000000);//black
               setBuff(0x00, 0x00, 0x00); //black
              }
            }
            break;
        }

         
        case 2:
        {
            if(state==false){
               // M5.dis.drawpix(i,0xffffff); //white
               setBuff(0xff, 0xff, 0xff); //white
              }
              else {
               // M5.dis.drawpix(i,0x000000);//black
               setBuff(0x00, 0x00, 0x00); //black
              }
            }
            break;
        }

 
        default:
            break;
        }
        M5.dis.displaybuff(DisBuff);

        FSM++;
        if (FSM >= 3)
        {
            FSM = 0;
        }
    }

    M5.update();
}
