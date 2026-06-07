#ifndef _ENTITY_H
#define _ENTITY_H

#include <raylib.h>

#define DEFAULT_ENTITY_SPEED  120.0f
#define ENTITY_FRICTION 1.0f
#define ENTITY_GRAVITY  1000.0f

typedef enum {
	STATE_AIR = 0x0,// In air
	STATE_GROUND,// In ground
	STATE_WALKING,// Walking
	STATE_IDLE,// Idle/AFK
} EntityState;

typedef struct {
	const char    *name;
	unsigned int  health;
	unsigned int  max_health;
	Vector2       pos;
	Vector2       velocity;
	float         speed;
	float         width, height;
	EntityState   state;
	Texture2D     sprite;
} Entity;

Rectangle get_entity_rect (Entity *e);
Entity* make_entity(const char *name, Texture2D sprite, unsigned int max_health,
					float speed, Vector2 pos, float width, float height);
void move_entity (Entity *e, Vector2 direction, float delta);

#endif
