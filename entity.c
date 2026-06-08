#include "entity.h"
#include "renplat.h"
#include "extern.h"
#include "raymath.h"

// TODO: Implement EntityTable so we can apply physic to all
//       Entity

Entity* make_entity (const char *name, Looks look, unsigned int max_health,
					float speed, Vector2 pos, float width, float height)
{
	Entity* e = (Entity *) xmalloc (sizeof(Entity));
	e->name = name;
	e->max_health = max_health;
	e->health = e->max_health;

	e->pos = pos;
	e->speed = speed;
	e->width = width;
	e->height = height;
	e->look = look;

	e->velocity = (Vector2){
		.x = 0,
		.y = 0,
	};

	e->state |= STATE_AIR;
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

void draw_entity (Entity *e)
{
	if ((e->look.flags & LOOK_SPRITE) && !(e->look.flags & LOOK_COLOR)
		&& IsTextureValid (e->look.as.sprite))
	{
		DrawTextureRec (e->look.as.sprite, get_entity_rect (e), e->pos, e->look.tint);
	}
	else  // Draw color
	{
		Color color;

		if (!(e->look.flags & LOOK_COLOR))  // Failed sprite texture load fallback
			color = WHITE;
		else
			color = e->look.as.color;

		DrawRectangle (e->pos.x, e->pos.y, e->width, e->height, color);
	}
}

void move_entity (Entity *e, Vector2 direction, float delta)
{
	Vector2 last_pos = e->pos;
	float length = sqrtf ( (direction.x * direction.x) + (direction.y * direction.y));
	if (length >1.0f)
	{
		direction.x /= length;
		direction.y /= length;
	}

	if (direction.x != 0)
		e->velocity.x = direction.x * e->speed;
	else
		e->velocity.x = Lerp (e->velocity.x, 0.0f, ENTITY_FRICTION * delta); // Smooth brake;

	if (direction.y != 0)
		e->velocity.y = direction.y * e->speed;
	else
		e->velocity.y = Lerp (e->velocity.y, 0.0f, ENTITY_FRICTION * delta); // Smooth brake;

	e->pos.x += e->velocity.x * delta;
	e->pos.y += e->velocity.y * delta;

/* XXX - Should add collision logic here */
/* XXX - Should add entity state logic here */

	if (fabsf (e->velocity.x) > 0.1f || fabsf (e->velocity.y) > 1.0f) {
		e->state &= ~STATE_IDLE;
		e->state |= STATE_WALKING;
	}
	else {
		e->state |= STATE_IDLE;
		e->state &= ~STATE_WALKING;
	}
}
