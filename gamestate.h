#ifndef GAMESTATE_H
#define GAMESTATE_H

#define NPLANES 10
#define MAX_X 320
#define MAX_Y 240
#define MAX_WIDTH 300
#define MAX_HEIGHT 220

#define GREEN 0x27B3

typedef struct{
	int width;
	int height;
	int x;
	int y;
} plane;

typedef struct{
	int x;
	int y;
} spaceship;

typedef struct{
	int x;
	int y;
} asteroid;

typedef struct{
	plane planes[NPLANES];
	int farthestIndex;
	spaceship ship;
	asteroid ast;
} gamestate;


void initGamestate(gamestate *gs);

void updateGamestate(gamestate *gs);



#endif
