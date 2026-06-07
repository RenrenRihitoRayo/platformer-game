#include "entity.h"
#include "renplat.h"

Entity* make_entity(const char *name, Texture2D sprite, unsigned int health, Vector2 speed,
					Vector2 pos, float width, float height)
{
	Entity* e = (Entity *) xmalloc (sizeof(Entity));
	e->name = name;
	e->health = health;

	e->pos = pos;
	e->width = width;
	e->height = height;
	e->sprite = sprite;
	e->speed = speed;

	e->state = STATE_IN_AIR;
	return e;
}

Rectangle get_entity_rect (Entity *e)
{
	return (Rectangle){
		.x = e->pos.x,
		.y = e->pos.y,
		.width = e->width,
		.height = e->height,
	};
}

void move_entity (Entity *e, Vector2 pos)
{
	Rectangle rect = get_entity_rect (e);
	Vector2 last_pos = e->pos;

	e->pos.x = pos.x;
	e->pos.y = pos.y;

/* XXX 
	for (int i = 0; i < GAME.object_count; i++)
	{
		if (CheckCollisionRecs (rect, GAME.objects[i].rect))
		{
			e->pos.x = last_pos.x;
			e->pos.y = last_pos.y;
		}
	}
*/
}

void move_entity_relative (Entity *e, Vector2 pos)
{
	Vector2 new_pos = (Vector2){
		.x = (e->pos.x + pos.x),
		.y = (e->pos.y + pos.y),
	};
	move_entity (e, new_pos);
}
