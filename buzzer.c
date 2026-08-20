//buzzer.c
#include "lpc214x.h"
#include "buzzer.h"
#include "delay.h"

void PulseBuzzer(void) {
    IOSET0 = BUZZER;
    delay_ms(100);
    IOCLR0 = BUZZER;
}
