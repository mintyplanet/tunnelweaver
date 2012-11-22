#ifndef RENDER_H
#define RENDER_H
#include "gamestate.h"

typedef short pixelbuffer[MAX_X][MAX_Y];



//creates the inital array of squares
void pixelBufferInit(pixelbuffer buffer);

void inline writePixel(int x, int y, short colour);

void writeOnBuffer(int x, int y, short colour, pixelbuffer buffer);

//clear the buffer
void clearBuffer(pixelbuffer buffer);

void drawRectangle(int x, int y, int width, int height, short colour, pixelbuffer buffer);

void drawCircle(int y, int x, int r, short colour, pixelbuffer buffer);

//write the buffer to the screen
void writeBufferToScreen(pixelbuffer buffer);


void drawGamestate(gamestate *gs, pixelbuffer buffer);



#endif
