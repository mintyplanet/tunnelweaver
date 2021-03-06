
#ifndef TIMER_H
#define TIMER_H

#define Timer 0x10002000
#define TimerStatus ((volatile short*) (Timer))
#define TimerControl ((volatile short*) (Timer+4))
#define TimerTimeoutL ((volatile short*) (Timer+8))
#define TimerTimeoutH ((volatile short*) (Timer+12))
#define TimerSnapshotL ((volatile short*) (Timer+16))
#define TimerSnapshotH ((volatile short*) (Timer+20))

#define LO_HALFWORD(word) (word & 0xFFFF)
#define HI_HALFWORD(word) ((word>>16) & 0xFFFF)
#define TIMEOUT ((*(TimerStatus))&0x1)


void delay(int ms);
//void usleep(int us);

#endif
