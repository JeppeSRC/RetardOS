#pragma once

#include "sys.h"

#ifdef CMOS_RTC_ENABLED_NMI
#define CMOS_RTC_NMI 
#else
#define CMOS_RTC_NMI 0x80
#endif

#define CMOS_RTC_PORT_BASE 0x70
#define CMOS_RTC_PORT_READ_WRITE 0x71
#define CMOS_RTC_REG_SECONDS ((unsigned char)0x00 | CMOS_RTC_NMI)
#define CMOS_RTC_REG_MINUTES (0x02 | CMOS_RTC_NMI)
#define CMOS_RTC_REG_HOURS (0x04 | CMOS_RTC_NMI)
#define CMOS_RTC_REG_DAY_OF_WEEK (0x06 | CMOS_RTC_NMI)
#define CMOS_RTC_REG_DAY_OF_MONTH (0x07 | CMOS_RTC_NMI)
#define CMOS_RTC_REG_MONTH (0x08 | CMOS_RTC_NMI)
#define CMOS_RTC_REG_YEAR (0x09 | CMOS_RTC_NMI)
#define CMOS_RTC_REG_CENTURY (0x32 | CMOS_RTC_NMI)
#define CMOS_RTC_REG_STATUS_A (0x0A | CMOS_RTC_NMI)
#define CMOS_RTC_REG_STATUS_B (0x0B | CMOS_RTC_NMI)
#define CMOS_RTC_REG_STATUS_C (0x0C | CMOS_RTC_NMI)
#define CMOS_RTC_REG_STATUS_D (0x0D | CMOS_RTC_NMI)

#define CHECKBIT(v, bit) ((v & (1 << (bit))) > 0)
#define BCD_TO_BINARY(bcd) ((((bcd) / 16) * 10) + (bcd & 0x0F))


struct CMOS_RTC_Time {
	unsigned char seconds;
	unsigned char secondsAlarm;
	unsigned char minutes;
	unsigned char minutesAlarm;
	unsigned char hours;
	unsigned char hoursAlarm;
	unsigned char dayOfWeek;
	unsigned char dayOfMonth;
	unsigned char months;
	unsigned char years;
};

struct CMOS_RTC_Status_A {
	unsigned char dividerRate : 4;
	unsigned char dividerStage : 3;
	bool updateInProgress : 1;
};

struct CMOS_RTC_Status_B {
	bool daylightSaving : 1;
	bool time24HourMode : 1;
	bool timeBinaryFormat : 1;
	bool squareWaveFrequency : 1;
	bool updateEndInterrupt : 1;
	bool alarmInterrupt : 1;
	bool periodicInterrupt : 1;
	bool disableClockUpdate : 1;
};

struct CMOS_RTC_Status_C {
	unsigned char reserved : 4;
	bool updateEndInterrupt : 1;
	bool alarmInterrupt : 1;
	bool periodicInterrupt : 1;
	bool IRQFFlag : 1;
};

struct CMOS_RTC_Status_D {
	unsigned char reserved : 7;
	bool cmosRamHasPower : 1;
};

struct CMOS_RTC_State{
	CMOS_RTC_Time time;
	CMOS_RTC_Status_A statusA;
	CMOS_RTC_Status_B statusB;
	CMOS_RTC_Status_C statusC;
	CMOS_RTC_Status_D statusD;
};

void CMOS_RTC_GetState(CMOS_RTC_State* state, bool includeDateAndTime = false);

void CMOS_RTC_GetCurrentDateAndTime(CMOS_RTC_Time* dateAndTime);
void CMOS_RTC_GetCurrentDate(CMOS_RTC_Time* date);
void CMOS_RTC_GetCurrentTime(CMOS_RTC_Time* time);

void CMOS_RTC_GetStatusRegister(unsigned char reg, void* regStruct);
void CMOS_RTC_SetStatusRegister(unsigned char reg, void* regStruct);
