//lm35.c
#include "adc_defines.h"
#include "adc.h"
#include "types.h"

f32 Read_LM35(void)
{
    f32 eAR;          // Analog result in volts
    u16 dval;         // Digital ADC value
    static u32 flag;  // To initialize ADC only once

    if(flag == 0)
    {
        Init_ADC(AIN0);   // Select channel AIN0
        flag = 1;
    }

    Read_ADC(0, &dval, &eAR);  // Read ADC
    return (eAR * 100);   // LM35 ? 10mV per °C // So Temp = Voltage × 100
}
f32 Read_LM35_NP(void)
{
    f32 eAR1, eAR2, t;
    u16 dval1, dval2;
    static u32 flag;

    if(flag == 0)
    {
        Init_ADC(AIN0|AIN1);
        flag = 1;
    }

    Read_ADC(0, &dval1, &eAR1);
    Read_ADC(1, &dval2, &eAR2);

    t = (eAR1 - eAR2) * 100;

    return t;
}