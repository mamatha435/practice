// eint.h
#ifndef __EINT_H
#define __EINT_H

#include <lpc214x.h>
#include "types.h"

// Pin definitions
#define BUZZER       (1<<25)    // P0.25 or adjust according to your hardware
#define LED_EINT0    (1<<16)    // P1.16
#define LED_EINT1    (1<<17)    // P1.17

// Function prototypes
void EINT_Init(void);

void EINT0_Handler(void) __irq;

// ISR function prototypes (if needed to be called externally)
void eint0_isr(void) __irq;
void eint1_isr(void) __irq;

// External flag to indicate alarm
extern volatile unsigned char alarm_flag;

#endif  // __EINT_H
