#ifndef CONTROL_H
#define CONTROL_H

#define Pushbuttons ((volatile long *) 0x10000050)
// n is between 1 and 3. Key0 is reset button.
#define isKeyPressed(n) ( (*Pushbuttons)&(1<<n) )



#endif
