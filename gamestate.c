#include "gamestate.h"
#include <stdlib.h>

void initGamestate(gamestate *gs) {
	int i;
	//gs->planes = (plane*)malloc(NPLANES*sizeof(plane));
	for (i=0; i<NPLANES; i++) {
		plane *p = &(gs->planes[i]);

		p->x = MAX_X/2;
		p->y = MAX_Y/2;
		p->width = 30*i+20; //20-290
		p->height = 18*i+12; //12-174
	}
	gs->farthestIndex = 0;

	gs->ship.x = MAX_X/2;
	gs->ship.y = MAX_Y*3/4;
}

void updateGamestate(gamestate *gs) {
	int i;
	int closestIndex = (NPLANES+gs->farthestIndex-1)%NPLANES;
	plane *closest = &(gs->planes[closestIndex]);
	if ((closest->width > MAX_WIDTH) ||
		(closest->height > MAX_HEIGHT)) {
		//The closest (outermost) plane is oversized.
		//Resize it and reassign it as the farthest plane
		closest->width = 20;
		closest->height = 12;
		gs->farthestIndex=closestIndex;
	}
	for (i=0; i<NPLANES; i++) {
		plane *p = &(gs->planes[i]);

		p->width+=3;
		p->height+=3;
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
	}
}


