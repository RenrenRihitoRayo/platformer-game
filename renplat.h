#ifndef _MAIN_H
#define _MAIN_H

#include "entity.h"
#include <stdlib.h>
#include <raylib.h>

#define RENPLAT_GAMEFPS  30
#define RENPLAT_PLAYER_WIDTH 10
#define RENPLAT_PLAYER_HEIGHT 50

#define GRAV 1
#define JUMP_POW 20
#define PLAYER_SPEED 5

#ifndef inline
 #define inline
#endif

typedef unsigned char   byte;

typedef struct
{
	/* Make object */
} GameMap;

typedef struct
{
	GameMap map;
	Entity *player;
} GameState;

extern void* xmalloc(size_t size);

extern GameState GAME;

#endif
