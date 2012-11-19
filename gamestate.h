#ifndef GAMESTATE_H
#define GAMESTATE_H

#define NPLANES 10
#define MAX_X 320
#define MAX_Y 240
#define MAX_WIDTH 300
#define MAX_HEIGHT 220
#define Asteroid 0x09F1
#define GREEN 0x27B3
#define AST_RATIO_X 2
#define AST_RATIO_Y 1.5

typedef struct{
	int width;
	int height;
	int x;
	int y;
	asteroid ast;
} plane;

typedef struct{
	int x;
	int y;
} spaceship;

typedef struct{
	int x;
	int y;
	int r;
} asteroid;

typedef struct{
	plane planes[NPLANES];
	int farthestIndex;
	spaceship ship;
} gamestate;


void initGamestate(gamestate *gs);

void updateGamestate(gamestate *gs);



#endif
