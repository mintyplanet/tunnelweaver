#include "gamestate.h"
//#include <stdlib.h>
#define SQUARED(x) ((x)*(x))
void initGamestate(gamestate *gs) {
	int i;
	//gs->planes = (plane*)malloc(NPLANES*sizeof(plane));
	for (i=0; i<NPLANES; i++) {
		plane *p = &(gs->planes[i]);
		// only draw asteroid on the furthest plane, set others to 0.
		if(i == 0){
			int Xdisplace = rand() % 20;
			int Ydisplace = rand() % 12;
			p->ast.r = 1;
			p->ast.x = MAX_X/2- 10 + Xdisplace;
			p->ast.y = MAX_Y/2- 6 + Ydisplace;
		}else {
			p->ast.r = 0;
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

int detectCollision(gamestate *gs) {
	int closestIndex = (NPLANES+gs->farthestIndex-1)%NPLANES;
	plane *closest = &(gs->planes[closestIndex]);
	asteroid *ast = &(closest->ast);
	spaceship *ship = &(gs->ship);
	return (SQUARED(ship->x-ast->x)+SQUARED(ship->y-ast->y)) < SQUARED(ast->r+7);
	
		
}

void updateGamestate(gamestate *gs) {
	int i;
	static x = 0;
	x++;
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
		closest->ast.r = 1;
		closest->ast.x = MAX_X/2- 10 + Xdisplace;
		closest->ast.y = MAX_Y/2- 6 + Ydisplace;
		gs->farthestIndex=closestIndex;
	}
	for (i=0; i<NPLANES; i++) {
		plane *p = &(gs->planes[i]);
		//if no asteroid, do not increase radius, else increase the asteroid size and shift asteroid.
		if (p->ast.r != 0){
		
			if (x % 3 == 0){
				p->ast.r += 1;
			}

			if (p->ast.x - MAX_X/2 < 0){
				p->ast.x -= rand() % 3;//AST_RATIO_X;	
			} else{
				p->ast.x += rand() % 3;//AST_RATIO_X;
			}
			if (p->ast.y - MAX_Y/2 < 0){
				p->ast.y -= rand() % 3;//AST_RATIO_Y;	
			} else{
				p->ast.y += rand() % 3;//AST_RATIO_Y;
			}
		}

		p->width+=4;
		p->height+=3;
	}
}
