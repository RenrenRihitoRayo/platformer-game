#ifndef _ENTITY_H
#define _ENTITY_H

#include <raylib.h>

typedef enum {
	STATE_IN_AIR = 0x0,
	STATE_ON_SOMETHING
} EntityState;

typedef struct {
	const char      *name;
	unsigned int    health;
	Vector2         pos;
	float           width, height;
	EntityState     state;
	Texture2D       sprite;
} Entity;

Rectangle get_entity_rect (Entity *e);
Entity* make_entity(const char *name, Texture2D sprite, unsigned int health, int x,
					int y, float width, float height);
void move_entity (Entity *e, Vector2 pos);
void move_entity_relative (Entity *e, Vector2 pos);

#endif
