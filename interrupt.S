.include "nios_macros.s"

.equ TIMERADDR, 0x10002000 

.global TimerInit

TimerInit:
	subi sp, sp, 8
	stw r16, 0(sp)
	stw r17, 4(sp)
	movui r17, 0b1        /*Enable interrupts globally in the processor*/
	wrctl ctl0, r17
	MOVI32 r16, TIMERADDR
	movui r17, 0xF080  	/* change number here*/
	stwio r17, 8(r16)        	/* set lower 16 bits of timer*/
	movui r17, 0x2FA
	stwio r17, 12(r16)	/* set upper 16 bits of timer*/
	stwio r0, 0(r16)         /* Reset timeout just to be sure.*/
	movui r17, 0b111
	stwio r17, 4(r16)        /* Start timer and set continue bit high*/
	movui r17, 0b1             /* enable IRQ line*/
	wrctl ctl3, r17
	ldw r17 4(sp)
	ldw r16 0(sp)
	addi sp, sp, 8
ret

/*--------------------------------------------------------------------------------*/

.section .exceptions, "ax"

Handler:
	MOVI32 et, TIMERADDR

	stwio r0, 0(et)        /*clear timer*/
	addi sp, sp, -4
	stw ra, 0(sp)
	call TimerHandler        /*Adjust square sizes and send to screen*/
	
	ldw ra, 0(sp)
	addi sp, sp, 4