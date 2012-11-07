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

#define GREEN 0x27B3

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
	p->width = 100;
	p->height = 60;
	p->x = 160;
	p->y = 120;
	p->next = next;
}

void writePixel(int x, int y, short colour){
	volatile short *vga_addr=(volatile short*)(0x08000000 + (y<<10) + (x<<1));
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

void drawScaledPlane(plane *planes, pixelbuffer buffer, int depth) {
	float scale = (NPLANES-(depth+1)) / NPLANES;
	int width = planes->width * scale;
	int height = planes->height * scale;
	int x = planes->x;
	int y = planes->y;
	drawRectangle(x,y,width, height, GREEN+depth, buffer);
}

void drawPlanesToBuffer(plane *planes, pixelbuffer buffer) {
	int p;

	clearBuffer(buffer);
	for (p=0; p<NPLANES; p++, planes=planes->next) {
		drawScaledPlane(planes, buffer,p);
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
void updatePlane(plane **planes) {
	(*planes)->width=rand()%300;
	(*planes)->height=rand()%220;
	*planes = (*planes)->next;

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
	spaceship ship = {MAX_X/2, MAX_Y*3/4};

	pixelBufferInit(buffer);
	planesInit(&planes);

	// timerInit();
	while(1){
		delay(40);
		//drawPlanesToBuffer(planes, buffer);
		int depth;
		for (depth=0; depth<8; depth++) {
			
			drawRectangle(160,120,depth*40, depth*30, GREEN+depth*4, buffer);
		}
		drawShip(&ship, buffer);
		writeBufferToScreen(buffer);
		//get information from accelerometer
		
		
	}
	return 0;
 }
