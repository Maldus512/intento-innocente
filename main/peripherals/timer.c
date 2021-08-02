/*
 * File:   timer.c
 * Author: Virginia
 *
 * Created on 21 aprile 2021, 12.01
 */


#include "system.h"
#include "hardwareprofile.h"
#include "timer.h"
#include <stddef.h>
#include <stdlib.h>


static unsigned long millis = 0;


unsigned long get_millis(void) {
    unsigned long res;
    IEC0bits.T1IE   = 0;
    res = millis;
    IEC0bits.T1IE   = 1;
    return res;
}


void timer_init(void) {
    TMR1            = 0;
    T1CONbits.TCS   = 0;            // Internal Clock
    T1CONbits.TCKPS = 0;            // Clock source prescaler
    PR1             = 16030 - 1;     // Period, interrupt every 1ms at 32MHz
    T1CONbits.TON   = 1;            // Enable timer 1
    IPC0bits.T1IP   = 4;            // timer 1 interrupt priority
    IFS0bits.T1IF   = 0;
    IEC0bits.T1IE   = 1;             // Enable timer 1 interrupt  
}


void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {
    millis++;
    IFS0bits.T1IF = 0;
}
