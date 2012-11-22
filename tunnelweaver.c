/******************* 
 *A program that draws the pixels onto the screen of the game. The program will increase the size of each box in the screen by SizeIncreaseX and SizeIncreaseY when called.
 * The program will resize the box to MINX AND MINY, when X, Y of the box reaches MAXX and MAXY.
 */
#include "gamestate.h"
#include "render.h"
#include "control.h"

int main(){
	pixelbuffer buffer;
	gamestate gs;

	pixelBufferInit(buffer);
	initGamestate(&gs);

/*
		writeBufferToScreen(buffer);
		#define OFFSET 10
writePixel(OFFSET, OFFSET, GREEN);
writePixel(160, OFFSET, GREEN);
writePixel(319-OFFSET, OFFSET, GREEN);
writePixel(OFFSET, 120, GREEN);
writePixel(OFFSET, 239-OFFSET, GREEN);
writePixel(160, 239-OFFSET, GREEN);
writePixel(319-OFFSET, 120, GREEN);
writePixel(319-OFFSET, 239-OFFSET, GREEN);
return;
*/

	// timerInit();
	while(!detectCollision(&gs)){
		//delay(40);

		drawGamestate(&gs, buffer);
		//drawCircle(200,60,12,GREEN,buffer);
		writeBufferToScreen(buffer);
		//get information from accelerometer
		if( isKeyPressed(1)) gs.ship.x++;
		if( isKeyPressed(3)) gs.ship.x--;
		updateGamestate(&gs);
		
	}
	return 0;
 }
