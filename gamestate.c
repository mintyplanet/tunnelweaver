#include "gamestate.h"
//#include <stdlib.h>

void initGamestate(gamestate *gs) {
	int i;
	//gs->planes = (plane*)malloc(NPLANES*sizeof(plane));
	for (i=0; i<NPLANES; i++) {
		plane *p = &(gs->planes[i]);
		// only draw asteroid on the furthest plane, set others to 0.
		if(i == 0){
			int Xdisplace = rand() % 20;
			int Ydisplace = rand() % 12;
			p->ast->r = 1;
			p->ast->x = MAX_X/2- 10 + Xdisplace;
			p->ast->y = MAX_Y/2- 6 + Ydisplace;
		}else {
			p->ast->r = 0;
		}

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
		// randomize position of asteroid
		int Xdisplace = rand() % 20;
		int Ydisplace = rand() % 12;
		p->ast->r = 1;
		p->ast->x = MAX_X/2- 10 + Xdisplace;
		p->ast->y = MAX_Y/2- 6 + Ydisplace;
		gs->farthestIndex=closestIndex;
	}
	for (i=0; i<NPLANES; i++) {
		plane *p = &(gs->planes[i]);
		//if no asteroid, do not increase radius, else increase the asteroid size and shift asteroid.
		if (p->ast->r != 0){
			p->ast->r += 2;
			p->ast->x = (p->ast->x - MAX_X/2) * AST_RATIO_X + MAX_X/2;
			p->ast->y = (p->ast->y - MAX_Y/2) * AST_RATIO_Y + MAX_Y/2;
		}

		p->width+=3;
		p->height+=3;
	}
}

