#include "cmos.h"
#include "memory.h"
#include "stdio.h"

void CMOS_RTC_GetState(CMOS_RTC_State* state, bool includeDateAndTime) {
	if (includeDateAndTime) {
		CMOS_RTC_GetCurrentDateAndTime(&state->time);
	}

	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_STATUS_A);
	_inb(CMOS_RTC_PORT_READ_WRITE, &state->statusA);

	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_STATUS_B);
	_inb(CMOS_RTC_PORT_READ_WRITE, &state->statusB);

	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_STATUS_C);
	_inb(CMOS_RTC_PORT_READ_WRITE, &state->statusC);

	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_STATUS_D);
	_inb(CMOS_RTC_PORT_READ_WRITE, &state->statusD);
}

void CMOS_RTC_GetCurrentDateAndTime(CMOS_RTC_Time* dateAndTime) {
	CMOS_RTC_GetCurrentDate(dateAndTime);
	CMOS_RTC_GetCurrentTime(dateAndTime);
}

void CMOS_RTC_GetCurrentDate(CMOS_RTC_Time* date) {

	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_DAY_OF_WEEK);
	date->dayOfWeek = _inb(CMOS_RTC_PORT_READ_WRITE);

	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_DAY_OF_MONTH);
	date->dayOfMonth = _inb(CMOS_RTC_PORT_READ_WRITE);

	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_MONTH);
	date->dayOfMonth = _inb(CMOS_RTC_PORT_READ_WRITE);
	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_YEAR);
	date->years = _inb(CMOS_RTC_PORT_READ_WRITE);

}

void CMOS_RTC_GetCurrentTime(CMOS_RTC_Time* time) {


	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_SECONDS);
	unsigned char s = _inb(CMOS_RTC_PORT_READ_WRITE);

	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_MINUTES);
	unsigned char m = _inb(CMOS_RTC_PORT_READ_WRITE);

	_outb(CMOS_RTC_PORT_BASE, CMOS_RTC_REG_HOURS);
	unsigned char h = _inb(CMOS_RTC_PORT_READ_WRITE);

	CMOS_RTC_Status_B b;
	CMOS_RTC_GetStatusRegister(CMOS_RTC_REG_STATUS_B, &b);

	bool pm = CHECKBIT(h, 7);
	h &= 0x7F;

	if (!b.timeBinaryFormat) {
		s = BCD_TO_BINARY(s);
		m = BCD_TO_BINARY(m);
		h = BCD_TO_BINARY(h);
	}

	if (!b.time24HourMode) {
		if (pm) {
			h += 12; 
			if (h == 24) h = 0;
		}
	}


	time->seconds = s;
	time->minutes = m;
	time->hours = h;
}

void CMOS_RTC_GetStatusRegister(unsigned char reg, void* regStruct) {
	if (reg >  (CMOS_RTC_REG_STATUS_A & 0x7F) && (reg < CMOS_RTC_REG_STATUS_D & 0x7F)) {
		memset(regStruct, 0, 1);
		return;
	}

	_outb(CMOS_RTC_PORT_BASE, reg);
	_inb(CMOS_RTC_PORT_READ_WRITE, regStruct);
}

void CMOS_RTC_SetStatusRegister(unsigned char reg, void* regStruct) {
	if (reg >= (CMOS_RTC_REG_STATUS_A & 0x7F) && (reg <= CMOS_RTC_REG_STATUS_B & 0x7F)) {
		return;
	}

	_outb(CMOS_RTC_PORT_BASE, reg);
	_outb(CMOS_RTC_PORT_READ_WRITE, regStruct);
}