#include "timer.h"

void delay(int ms) {
	int cycles = 50000 * ms;
	*(TimerTimeoutL)=LO_HALFWORD(cycles);
	*(TimerTimeoutH)=HI_HALFWORD(cycles);
	*(TimerControl)=4;
	while(!TIMEOUT) {}
}

void usleep(int us) {
	int cycles = 50 * us;
	*(TimerTimeoutL)=LO_HALFWORD(cycles);
	*(TimerTimeoutH)=HI_HALFWORD(cycles);
	*(TimerControl)=4;
	while(!TIMEOUT) {}
}
