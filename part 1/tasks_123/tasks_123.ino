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
    delay(10);
    setBuff(0x00, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);
}



void loop()
{
    if (M5.Btn.wasPressed())
    {

        switch (FSM)
        {

        case 0:
         {         
          setBuff(0x00, 0x00, 0x00); //BLACK
          
          break;
          }
         
        case 1:        
         {
           currentTime=millis(); //millis retrieves current time and stores it into variable currentTime
           if(currentTime-previousTime>=1000){ //if 1 second passed, switch LED color
              
              if(state==false){
                setBuff(0xff, 0xff, 0xff); //white
                state=true;
              }
              else {
                setBuff(0x00, 0x00, 0x00); //black
                state=false;
              }
              
            previousTime=currentTime;
            }
            break;
        }

         
        case 2:
        {
           currentTime=millis(); //millis retrieves current time and stores it into variable currentTime
           if(currentTime-previousTime>=1000){ //if 1 second passed, switch LED color
              
              if(state==false){
                setBuff(0xff, 0x00, 0x00); //red
                state=true;
              }
              else {
                setBuff(0x00, 0x00, 0x00); //black
                state=false;
              }
              
            previousTime=currentTime;
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

    delay(50);
    M5.update();
}
