/******************* 
 *A program that draws the pixels onto the screen of the game. The program will increase the size of each box in the screen by SizeIncreaseX and SizeIncreaseY when called.
 * The program will resize the box to MINX AND MINY, when X, Y of the box reaches MAXX and MAXY.
 */
#include "gamestate.h"


//creates the inital array of squares
void pixelBufferInit(pixelbuffer buffer){
	int x,y;
	for(x=0; x<MAX_X; x++) {
		for (y=0; y<MAX_Y; y++) {
			buffer[x][y] = 0x0000;
		}
	}
}

void writePixel(int x, int y, short colour){
	volatile short *vga_addr=(volatile short*)(0x08000000 + (y<<10) + (x<<1));
	*vga_addr=colour;
}




void writeOnBuffer(int x, int y, short colour, pixelbuffer buffer) {
	if (0<=x && x<MAX_X && 0<= y && y<MAX_Y) {
		buffer[x][y] = colour;
	}
}

//clear the buffer
void clearBuffer(pixelbuffer buffer) {
	pixelBufferInit(buffer);
}

void drawRectangle(int x, int y, int width, int height, int colour, pixelbuffer buffer) {
	int i;
	int ytop = y-(height/2);
	int ybottom = y+(height/2);
	int xleft = x-(width/2);
	int xright = x+(width/2);
	
	for(i=ytop; i<=ybottom; i++) {
		writeOnBuffer(xleft, i, colour, buffer);
		writeOnBuffer(xright, i, colour, buffer);
	}
	for (i=xleft; i<=xright; i++) {
		writeOnBuffer(i, ytop, colour, buffer);
		writeOnBuffer(i, ybottom, colour, buffer);
	}
}


void drawShip(spaceship *ship, pixelbuffer buffer) {
#define SHIPSIZE 15
	static short shipBitmap[SHIPSIZE][SHIPSIZE] = 
	{
		{0,0,0,0,0,0,0,0xF800,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0xF800,0xF800,0xF800,0,0,0,0,0,0},
		{0,0,0,0,0,0,0xF800,0xF800,0xF800,0,0,0,0,0,0},
		{0,0,0,0,0,0xF800,0xF800,0xF800,0xF800,0xF800,0,0,0,0,0},
		{0,0,0,0,0xF800,0xF800,0xFFFF,0xFFFF,0xFFFF,0xF800,0xF800,0,0,0,0},
		{0,0,0,0,0xF800,0xF800,0xFFFF,0xFFFF,0xFFFF,0xF800,0xF800,0,0,0,0},
		{0,0,0xFFE0,0,0xF800,0xF800,0xFFFF,0xFFFF,0xFFFF,0xF800,0xF800,0,0xFFE0,0,0},
		{0,0,0xFFFF,0,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0,0xFFFF,0,0},
		{0,0,0xFFFF,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xFFFF,0,0},
		{0,0,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0,0},
		{0,0,0xF800,0xF800,0xF800,0xF800,0xF800,0xFFE0,0xF800,0xF800,0xF800,0xF800,0xF800,0,0},
		{0,0xF800,0xF800,0xFFE0,0xF800,0xF800,0xF800,0xFFE0,0xF800,0xF800,0xF800,0xFFE0,0xF800,0xF800,0},
		{0,0xF800,0xF800,0xFFE0,0xF800,0xF800,0xF800,0xFFE0,0xF800,0xF800,0xF800,0xFFE0,0xF800,0xF800,0},
		{0xF800,0xF800,0xFFE0,0xFFE0,0xF800,0xF800,0xF800,0xFFE0,0xF800,0xF800,0xF800,0xFFE0,0xFFE0,0xF800,0xF800}
	};
	int x,y;
	for (x=0; x<SHIPSIZE; x++){
	for (y=0; y<SHIPSIZE; y++){
		if (shipBitmap[y][x]) {
			writeOnBuffer((ship->x)+x-(SHIPSIZE/2) ,(ship->y)+y-(SHIPSIZE/2), shipBitmap[y][x], buffer);
		}
	}}
	
}

//write the buffer to the screen
void writeBufferToScreen(pixelbuffer buffer){
	int x,y;
	for (x=0; x<MAX_X; x++){
	for (y=0; y<MAX_Y; y++){
		writePixel(x,y,buffer[x][y]);
	}}
}

/*
 extern void TimerHandler(){
	adjustSize();
	clearBuffer();
	writeArrayToBuffer();
	writeBufferToScreen(); 
}
*/

int main(){
	 
	pixelbuffer buffer;
	gamestate gs;

	pixelBufferInit(buffer);
	initGamestate(&gs);

	// timerInit();
	while(1){
		//delay(40);

		drawGamestate(&gs, buffer);
		drawShip(&gs.ship, buffer);
		writeBufferToScreen(buffer);
		//get information from accelerometer
		updateGamestate(&gs);
		
	}
	return 0;
 }
