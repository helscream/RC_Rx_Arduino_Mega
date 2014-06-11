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
#ifndef rc_rx.h
  #define rc_rx.h
  
  extern float CH1,CH2,CH3,CH4,CH5,CH6,CH7;
  
  void init_rc_rx();
  void read_rc_rx();  
#endif
