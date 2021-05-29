# m5-bikelights
 atom/arduino

#include <SoftwareSerial.h>

void setup() {
  // put your setup code here, to run once:
 
      pinMode(red_light_pin, OUTPUT); //what's red_light_pin??

}


void loop() {
  // put your main code here, to run repeatedly:
  
  int sensorValue = Serial.read(); //reads accelerometer value
  int j=sensorValue; //to store previous value
  delay(1000) //wait for one second
  sensorValue = Serial.read(); //read the current value
    
    if (sensorValue>=j) //if car is accelerating/not braking(decelerating), strobe lights
    {
          //continuous light strobing
          int red_light_pin= 11; //is this necessary
          
          int green_light_pin = 10;
          
          int blue_light_pin = 9;
          
            RGB_color(255, 0, 0); // Red
          
            delay(1000);
  
            void clear() //Close all of LEDs
          
            delay(1000);
         
          void RGB_color(int red_light_value, int green_light_value, int blue_light_value) //is this necessary
          
          
           {
          
            analogWrite(red_light_pin, red_light_value);
          
            analogWrite(green_light_pin, green_light_value);
          
            analogWrite(blue_light_pin, blue_light_value);
          
          }
    }
    
    elseif (sensorValue<j)//it's decelerating
    {   
            RGB_color(255, 0, 0); // display solid Red color
          
            delay(1000);
    }
    
}