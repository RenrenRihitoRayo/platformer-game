#include "entity.h"
#include "renplat.h"

Entity* make_entity(const char *name, Texture2D sprite, unsigned int health, int x,
					int y, float width, float height)
{
	Entity* entity = (Entity *) xmalloc (sizeof(Entity));
	entity->name = name;
	entity->health = health;

	entity->pos.x = x;
	entity->pos.y = y;
	entity->width = width;
	entity->height = height;
	entity->sprite = sprite;

	entity->state = STATE_IN_AIR;
	return entity;
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

	if (e->pos.x < 0 || e->pos.x > (float)GetScreenWidth ())
		e->pos.x = last_pos.x;
	if (e->pos.y < 0 || e->pos.y > (float)GetScreenHeight ())
		e->pos.y = last_pos.y;

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
