//delay.c

/* Creates a delay in Microseconds (us) Assumption: The loop runs roughly 12 times per microsecond */
void delay_us(unsigned int dlyus)
{
    // Multiply input by 12 to scale the loop for microseconds
    // Then decrement until it reaches 0
    for(dlyus *= 12; dlyus > 0; dlyus--);
}

/* Creates a delay in Milliseconds (ms) 1 ms = 1,000 us. Therefore, 12 * 1,000 = 12,000  */
void delay_ms(unsigned int dlyms)
{
    // Multiply input by 12,000 to scale the loop for milliseconds
    // This blocks the CPU from doing other tasks for the duration
    for(dlyms *= 12000; dlyms > 0; dlyms--);
}

/* Creates a delay in Seconds (s)   1 s = 1,000 ms. Therefore, 12,000 * 1,000 = 12,000,000 */
void delay_s(unsigned int dlys)
{
    // Multiply input by 12,000,000 to scale the loop for full seconds
    // Note: 'unsigned int' must be 32-bit to hold these large numbers
    for(dlys *= 12000000; dlys > 0; dlys--);
}
