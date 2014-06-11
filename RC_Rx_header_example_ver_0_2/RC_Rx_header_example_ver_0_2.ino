/*
Author:    Omer Ikram ul Haq
Date:      2014-06-11
Location:  Pakistan
Version:   ver 0.2 beta
Test with: Arduino Mega and Devention rx701
*/

/* ----------------------------------------
Versions:
    Ver 0.2 beta:	Addition of PinChange Interrupt support and Channel 5 - 7 
			are using PinChange interrupts "PinChangeInt.h".
	          Bug fixed: 	Built-in Pull-up resistors are activated

    Ver 0.1 beta: 	Initial version. Only supports Hardware interrupts and 
			maximum number of Channels are 4

*/

#include "rc_rx.h"

#define led 13
#define dt 20         // [ms] Task time 

unsigned long t=0;

void setup()
{
  Serial.begin(115200); // Initializing serial port before calling init_rc_rx() function 
  init_rc_rx();
  pinMode(led, OUTPUT);
}

void loop()
{ 
  t = micros()/1000;
  read_rc_rx();        // CH1, CH2, CH3 and CH4 float variables will be calculated 
                       // and updated when this function is called
  analogWrite(led,2.55*CH1);
  
  
  print_value(CH1);
  print_value(CH2);
  print_value(CH3);
  print_value(CH4);
  print_value(CH5);
  print_value(CH6);
  print_value(CH7);
  Serial.println(((micros()/1000)- (float)t)*100/dt);
  
  
  while (dt > (micros()/1000)- t){
  // do nothing
  }
  
  
}

void print_value(float input){
	if (input < -100){
		Serial.print("NA");
	}else {
		Serial.print(input);
	}
	Serial.print("\t");
}


