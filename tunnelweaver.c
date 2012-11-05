/******************* 
 *A program that draws the pixels onto the screen of the game. The program will increase the size of each box in the screen by SizeIncreaseX and SizeIncreaseY when called.
 * The program will resize the box to MINX AND MINY, when X, Y of the box reaches MAXX and MAXY.
 */

#include <stdlib.h>
 
 #define MINY 20
 #define MINX 10
 #define MAXY 240
 #define MAXX 360
 #define SizeIncreaseX 10 
 #define SizeIncreaseY 10

#define NPLANES 10
#define MAX_X 320
#define MAX_Y 240

typedef short pixelbuffer[MAX_X][MAX_Y];

typedef struct plane{
	int width;
	int height;
	int x;
	int y;
	struct plane *next;
} plane;

typedef struct{
	int x;
	int y;
} spaceship;

//creates the inital array of squares
void pixelBufferInit(pixelbuffer buffer){
	int x,y;
	for(x=0; x<MAX_X; x++) {
		for (y=0; y<MAX_Y; y++) {
			buffer[x][y] = 0x0000;
		}
	}
}
void planeInit(plane *p, plane *next) {
	p->width = 0;
	p->height = 0;
	p->x = 0;
	p->y = 0;
	p->next = next;
}

void writePixel(int x, int y, short colour){
	volatile short *vga_addr=(volatile short*)(0x08000000 + (y<<10) + (x<<1);
	*vga_addr=colour;
}


/*Create a circular linked list of planes */
void planesInit(plane **planes) {
	int p;
	plane *last = malloc(sizeof(plane));
	plane *prev, *next = last;

	for (p=1; p<NPLANES; p++) {
		prev = malloc(sizeof(plane));
		planeInit(prev, next);
		next = prev;
	}
	planeInit(last, prev);
	*planes = prev;
}

//clear the buffer
void clearBuffer(pixelbuffer buffer) {
	pixelBufferInit(buffer);
}

void drawPlanesToBuffer(plane *planes, pixelbuffer buffer) {
	int p;

	clearBuffer(buffer);
	for (p=0; p<NPLANES; p++, planes=planes->next) {
		drawScaledPlaneToBuffer(planes, buffer,p);
	}
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
	 
	plane *planes;
	pixelbuffer buffer;
	spaceship ship = {MAX_X/2, MAX_Y/2};

	pixelBufferInit(buffer);
	planesInit(&planes);

	// timerInit();
	while(1){
		//get information from accelerometer
	}
	return 0;
 }
