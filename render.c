#include "render.h"
#include "gamestate.h"
#include "control.h"

//creates the inital array of squares
void pixelBufferInit(pixelbuffer buffer){
	int x,y;
	for(x=0; x<MAX_X; x++) {
		for (y=0; y<MAX_Y; y++) {
			buffer[x][y] = 0x0000;
		}
	}
}

void inline writePixel(int x, int y, short colour){
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

void drawRectangle(int x, int y, int width, int height, short colour, pixelbuffer buffer) {
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

void drawCircle(int y, int x, int r, short colour, pixelbuffer buffer) {
	int ytop = y-(r/2);
	int xleft = x-(r/2);
	int i,j, r2=r*r;

	for(i=0;i<=2*r;i++){
		for(j=0;j<=2*r;j++){
		int circle = (i-r)*(i-r)+(j-r)*(j-r);
			if (circle<r2) {
				writeOnBuffer(ytop+i,xleft+j,colour,buffer);
			}
			if (((circle-r2)<(4+r/2)) && ((circle-r2)>-(4+r/2))) {
				writeOnBuffer(ytop+i,xleft+j,ASTEROID_EDGE_COLOUR,buffer);
			}
			
		}
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
		}
	}
}

//write the buffer to the screen
#define SKIP 2
void writeBufferToScreen(pixelbuffer buffer){
	int x,y;
	static int even=0;
	
	for (y=even++%SKIP; y<MAX_Y; y+=SKIP){
		for (x=0; x<MAX_X; x++){
			writePixel(x,y,buffer[x][y]);
		}
	}
}


void drawGamestate(gamestate *gs, pixelbuffer buffer) {
	/* Need to draw from the farthest frame, to give the effect of depth */
	int i;

	clearBuffer(buffer);
	for (i=0; i<NPLANES; i++) {
		int x = (i+gs->farthestIndex)%NPLANES;
		plane *p = &(gs->planes[x]);
		drawRectangle(p->x,p->y,p->width,p->height,GREEN+i*4,buffer);
		drawCircle(p->ast.x, p->ast.y, p->ast.r, ASTEROID_COLOUR-i, buffer);
	}
	drawShip(&(gs->ship), buffer);
}

void gameover(pixelbuffer buffer) {

	int x,y;
	
	for (y=0; y<MAX_Y; y++) {
		for(x=0; x<MAX_X; x++) {
			writePixel(x,y,0x1234);
		}
	}
	drawString(30, 30, "GAMEOVER");
	
	
	int blue = 0x1234;
	int d;
	while(blue && !isKeyPressed(2)){
	for (y=0; y<MAX_Y; y++) {
		
		usleep(3000);
		for(x=0; x<MAX_X; x++) {
			writePixel(x,y,blue);
		}
		blue-=0x100;
	}
	}
	drawString(30,30,"        ");
}
	
	

void drawString(int x, int y, char *str) {
	while (*str) {
		drawChar(x,y,*str);
		x+=2;
		str++;
	}
}

void drawChar(int x,int y,char ch) {
	volatile short *charbuf_addr=(volatile short*)(CHARBUFFER + (y<<7) + (x));
	*charbuf_addr=ch;
}
	

