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

#include <Arduino.h>
#include "PinChangeInt.h"
#include "rc_rx.h"

/*
// First four channels are using Hardware interrupt
*/
#define CH1_int 0     // Channel 1 interrupt # 
#define CH1_pin 2     // Respective channel Hardware interrupt pin number

#define CH2_int 1     // Channel 2 interrupt # 
#define CH2_pin 3     // Respective channel Hardware interrupt pin number

#define CH3_int 4     // Channel 3 interrupt # 
#define CH3_pin 19     // Respective channel Hardware interrupt pin number

#define CH4_int 5     // Channel 4 interrupt # 
#define CH4_pin 18    // Respective channel Hardware interrupt pin number

/*
// Last three (CH5 to CH7) are using Pin Change interrupt
*/
#define CH5_pin 10
#define CH6_pin 11
#define CH7_pin 12

/*
    Other definitions
*/
#define valid_pulse_limit 2000 // [uS] Valid output high pulse time limit for RC controller
#define max_high_time 1895 // [uS] Maximum expected high time
#define min_high_time 1090 // [uS] Minimum expected high time

volatile unsigned long CH1_t=0, CH1_delta=0, CH2_t=0, CH2_delta=0, CH3_t=0, CH3_delta=0, CH4_t=0, CH4_delta=0 ;
float CH1,CH2,CH3,CH4;
volatile unsigned long CH5_t=0, CH5_delta=0, CH6_t=0, CH6_delta=0, CH7_t=0, CH7_delta=0;
float CH5,CH6,CH7 ;

/* //------------------------
// Interrupt ISRs
*/ // ------------------------
// Hardware Interrupt ISRs
void CH1_int_ISR()
{
  if ((micros()-CH1_t) < valid_pulse_limit){
    CH1_delta = micros()-CH1_t;
  }
  CH1_t = micros();
}

void CH2_int_ISR()
{
  if ((micros()-CH2_t) < valid_pulse_limit){
    CH2_delta = micros()-CH2_t;
  }
  CH2_t = micros();
}

void CH3_int_ISR()
{
  if ((micros()-CH3_t) < valid_pulse_limit){
    CH3_delta = micros()-CH3_t;
  }
  CH3_t = micros();
}

void CH4_int_ISR()
{
  if ((micros()-CH4_t) < valid_pulse_limit){
    CH4_delta = micros()-CH4_t;
  }
  CH4_t = micros();
}
/* ----------------------------
*/
// Pinchnage Interrupt ISRs
void CH5_int_ISR()
{
  if ((micros()-CH5_t) < valid_pulse_limit){
    CH5_delta = micros()-CH5_t;
  }
  CH5_t = micros();
}


void CH6_int_ISR()
{
  if ((micros()-CH6_t) < valid_pulse_limit){
    CH6_delta = micros()-CH6_t;
  }
  CH6_t = micros();
}


void CH7_int_ISR()
{
  if ((micros()-CH7_t) < valid_pulse_limit){
    CH7_delta = micros()-CH7_t;
  }
  CH7_t = micros();
}
/* // -----------------------------
  End ISRs
*/ // -----------------------------


// Call able function

void init_rc_rx(){
  
  Serial.print("Channel 1 connected to pin number....\t");
  Serial.println(CH1_pin);
  Serial.print("Channel 2 connected to pin number....\t");
  Serial.println(CH2_pin);
  Serial.print("Channel 3 connected to pin number....\t");
  Serial.println(CH3_pin);
  Serial.print("Channel 4 connected to pin number....\t");
  Serial.println(CH4_pin);
  Serial.print("Channel 5 connected to pin number....\t");
  Serial.println(CH5_pin);
  Serial.print("Channel 6 connected to pin number....\t");
  Serial.println(CH6_pin);
  Serial.print("Channel 7 connected to pin number....\t");
  Serial.println(CH7_pin);
  
  pinMode(CH1_pin, INPUT);
  pinMode(CH2_pin, INPUT);
  pinMode(CH3_pin, INPUT);
  pinMode(CH4_pin, INPUT);
  pinMode(CH5_pin, INPUT);
  pinMode(CH6_pin, INPUT);
  pinMode(CH7_pin, INPUT);
  
  // Writing the input ports to HIGH to use pull-up resistors
  digitalWrite(CH1_pin, HIGH);
  digitalWrite(CH2_pin, HIGH);
  digitalWrite(CH3_pin, HIGH);
  digitalWrite(CH4_pin, HIGH);
  digitalWrite(CH5_pin, HIGH);
  digitalWrite(CH6_pin, HIGH);
  digitalWrite(CH7_pin, HIGH);  
  
  attachInterrupt(CH1_int, CH1_int_ISR, CHANGE);
  attachInterrupt(CH2_int, CH2_int_ISR, CHANGE);
  attachInterrupt(CH3_int, CH3_int_ISR, CHANGE);
  attachInterrupt(CH4_int, CH4_int_ISR, CHANGE);
  PCintPort::attachInterrupt(CH5_pin, CH5_int_ISR, CHANGE);
  PCintPort::attachInterrupt(CH6_pin, CH6_int_ISR, CHANGE);
  PCintPort::attachInterrupt(CH7_pin, CH7_int_ISR, CHANGE);
}

void read_rc_rx(){
  noInterrupts();
  CH1 = ((float)CH1_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH2 = ((float)CH2_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH3 = ((float)CH3_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH4 = ((float)CH4_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH5 = ((float)CH5_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH6 = ((float)CH6_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH7 = ((float)CH7_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  interrupts();
}





