#ifndef _MAIN_H
#define _MAIN_H

#include "entity.h"
#include <stdlib.h>
#include <raylib.h>

#define RENPLAT_GAMEFPS  30
#define RENPLAT_PLAYER_WIDTH 10
#define RENPLAT_PLAYER_HEIGHT 50

#define PLAYER_SPEED   DEFAULT_ENTITY_SPEED

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
	GameMap  map;
	Entity   *player;
	Camera2D camera;
} GameState;

extern void* xmalloc(size_t size);

/* Global variable */
extern GameState GAME;
extern float  SCREEN_WIDTH;
extern float  SCREEN_HEIGHT;

#endif
