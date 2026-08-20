//External Interrupt Initialization
void InitEINT(void)
{
    // EINT0 ? P0.14
    PINSEL0 |= (1<<29);
    EXTMODE |= (1<<0);
    EXTPOLAR &= ~(1<<0);

    // EINT1 ? P0.15
    PINSEL0 |= (1<<31);
    EXTMODE |= (1<<1);
    EXTPOLAR &= ~(1<<1);

    VICIntEnable |= (1<<14)|(1<<15);

    VICVectCntl0 = (1<<5)|14;
    VICVectAddr0 = (u32)EINT0_Handler;

    VICVectCntl1 = (1<<5)|15;
    VICVectAddr1 = (u32)EINT1_Handler;
}