#pragma once

#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>

#define GRAV 1
#define JUMP_POW 20
#define PLAYER_SPEED 5

#define GET_PLAYER_REC(p) (Rectangle){.x = p->pos.x, .y = p->pos.y, .width=10, .height=50}

#define XSTR(x) #x
#define ABORT(msg) {fprintf("A"); }

typedef struct {
	char* flags;
	uint32_t size;
} Table;

typedef enum {
	STATE_IN_AIR,
	STATE_ON_SOMETHING
} JumpState;

typedef struct {
	bool is_texture; // true if texture is Texture2D, if not then its a Color
	union {
		Texture2D texture;
		Color color;
	} looks;
} Looks;

typedef struct {
	Rectangle pos;
	Looks look;
} Platform;

typedef struct {
	Platform** items;
	uint32_t count;
	uint32_t size;
} PlatformDA;

typedef struct {
	PlatformDA* platforms;
	Vector2 player_start;
} Map;

typedef struct {
	Vector2 pos;
	Table* effects; // for future use
	uint16_t health;
	JumpState state;
	Platform* current_platform; // track which platform player is on
} Player;
