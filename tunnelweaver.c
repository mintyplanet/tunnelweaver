/******************* 
 *A program that draws the pixels onto the screen of the game. The program will increase the size of each box in the screen by SizeIncreaseX and SizeIncreaseY when called.
 * The program will resize the box to MINX AND MINY, when X, Y of the box reaches MAXX and MAXY.
 */
#include "gamestate.h"
#include "render.h"
#include "control.h"
#include "ADXL345.h"

int main(){
	pixelbuffer buffer;
	gamestate gs;

	pixelBufferInit(buffer);
	initGamestate(&gs);


JP2_init();
int i;
for (i=0;i<128;i++){
	 if (I2C_Write(0,0, i, 0, 0)) {
	 	//break;
	 	printf("I2C 0x%X success?\n",i);	
	 }
	 //printf("fail\n");
}
printf("Done\n");return 0;
////////////////////////
	writeBufferToScreen(buffer);
	if(!ADXL345_init()){
		drawCircle(MAX_Y/2, MAX_X/2, 50, 0x1234, buffer);
		writeBufferToScreen(buffer);
		return 0;
	}
//////////////

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
