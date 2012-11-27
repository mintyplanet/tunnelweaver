#ifndef GAMESTATE_H
#define GAMESTATE_H

#define NPLANES 10
#define MAX_X 320
#define MAX_Y 240
#define MAX_WIDTH 300
#define MAX_HEIGHT 220
#define ASTEROID_COLOUR 0xBDF7
#define ASTEROID_EDGE_COLOUR 0x7BEF
#define GREEN 0x27B3
#define AST_RATIO_X 1
#define AST_RATIO_Y 1
//1.5

typedef struct{
	int x;
	int y;
	int r;
} asteroid;

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
	plane planes[NPLANES];
	int farthestIndex;
	spaceship ship;
} gamestate;


void initGamestate(gamestate *gs);

void updateGamestate(gamestate *gs);



#endif
