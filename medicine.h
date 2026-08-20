#ifndef MEDICINE_H
#define MEDICINE_H

#include "types.h"

#define MAX_MEDICINE_TIMINGS 10

//Shared Global Variables (extern ensures they are only allocated memory once in medicine.c)
extern u8 medicine_count;
extern u8 medicine_timings[MAX_MEDICINE_TIMINGS][3]; // [Index][Hour, Min, Sec]

// Logic Function Prototypes
void System_Menu(void);                      // The main UI entry point
void CheckMedicineTimings(u8 hour, u8 min, u8 sec); // Background monitor
void ConfigureMedicineTiming(void);          // User input for new alarm
void Edit_RTC_TimeDATE(void);                    // User input to change clock

#endif
