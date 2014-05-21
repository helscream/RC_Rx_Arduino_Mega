/*
Author:    Omer Ikram ul Haq
Date:      2014-05-18
Location:  Pakistan
Version:   ver 0.1 beta
Test with: Arduino Mega and Devention rx701
*/


#include <Arduino.h>
#include "rc_rx.h"



#define CH1_int 0     // Channel 1 interrupt # 
#define CH1_pin 2     // Respective channel Hardware interrupt pin number

#define CH2_int 1     // Channel 2 interrupt # 
#define CH2_pin 3     // Respective channel Hardware interrupt pin number

#define CH3_int 4     // Channel 3 interrupt # 
#define CH3_pin 19     // Respective channel Hardware interrupt pin number

#define CH4_int 5     // Channel 4 interrupt # 
#define CH4_pin 18    // Respective channel Hardware interrupt pin number

#define valid_pulse_limit 3000 // [uS] Valid output high pulse time limit for RC controller
#define max_high_time 1895 // [uS] Maximum expected high time
#define min_high_time 1090 // [uS] Minimum expected high time

volatile unsigned long CH1_t=0, CH1_delta=0, CH2_t=0, CH2_delta=0, CH3_t=0, CH3_delta=0, CH4_t=0, CH4_delta=0 ;
float CH1,CH2,CH3,CH4;


// Interrupt ISRs

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
  
  pinMode(CH1_pin, INPUT);
  pinMode(CH2_pin, INPUT);
  pinMode(CH3_pin, INPUT);
  pinMode(CH4_pin, INPUT);
  
  attachInterrupt(CH1_int, CH1_int_ISR, CHANGE);
  attachInterrupt(CH2_int, CH2_int_ISR, CHANGE);
  attachInterrupt(CH3_int, CH3_int_ISR, CHANGE);
  attachInterrupt(CH4_int, CH4_int_ISR, CHANGE);
}

void read_rc_rx(){
  CH1 = ((float)CH1_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH2 = ((float)CH2_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH3 = ((float)CH3_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH4 = ((float)CH4_delta-(float)min_high_time)*100/(max_high_time-min_high_time);

}





