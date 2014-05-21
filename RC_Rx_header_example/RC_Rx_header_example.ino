/*
Author:    Omer Ikram ul Haq
Date:      2014-05-18
Location:  Pakistan
Version:   ver 0.1 beta
Test with: Arduino Mega and Devention rx701
*/

#include "rc_rx.h"

#define led 13
#define dt 20         // [ms] Task time 


unsigned long t=0;

void setup()
{
  Serial.begin(115200); // Initlizing serial port before calling init_rc_rx() function 
  init_rc_rx();
    pinMode(led, OUTPUT);
}

void loop()
{ 
  t = micros()/1000;
  
  read_rc_rx();        // CH1, CH2, CH3 and CH4 float variables will be calculated with this function is called
    
  
  analogWrite(led,2.55*CH1);
  
  
  Serial.print(CH1);
  Serial.print("\t");
  Serial.print(CH2);
  Serial.print("\t");
  Serial.print(CH3);
  Serial.print("\t");
  Serial.print(CH4);
  Serial.print("\t");
  Serial.println(((micros()/1000)- (float)t)*100/dt);
  
  
  while (dt > (micros()/1000)- t){
  // do nothing
  }
  
  
}


