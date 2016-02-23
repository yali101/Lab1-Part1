/*  
 *  Class: ECE372a
 * 
 *  Group: 209
 *
 *  Lab: 1 Part 1
 * 
 *  File: main.c
 * 
 *  Member: Michael Harmon (Software)
 *          Abdul Rana (Hardware)
 *          James Beulke (System Integration)
 *          Ali Hassan (Quality Control)
 */
#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"

typedef enum STATEenum{
  start,
  stop
}STATE;

volatile STATE state = start;

#define PORTx_HIGH 1
#define PORTx_LOW 0

#define LATx_HIGH 1
#define LATx_LOW 0

#define START_LED LATGbits.LATG14
#define STOP_LED LATGbits.LATG12

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void){
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initLEDs();
    initSW();
    while(1){
      switch(state){
        case start:
          START_LED = LATx_HIGH;
          STOP_LED = LATx_LOW;
          break;
        case stop:
          START_LED = LATx_LOW;
          STOP_LED = LATx_HIGH;
          break;
      }
    }
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    PORTA;
    IFS1bits.CNAIF = 0;
    delayUs(5000);
    if(PORTAbits.RA7 == PORTx_LOW){// Button Pressed
      if(state == start)state = stop;
      else if(state == stop)state = start;
    }else if(PORTAbits.RA7 = PORTx_HIGH){// Button Released
      
      // Do Nothing
    }
}