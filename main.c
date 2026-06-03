#include <raylib.h>
#include <stdlib.h>
#include <stdint.h>

#include "main.h"
#include "commons.h"

Texture2D player_tex = {0};
Player player = {0};

Player* make_player(uint16_t health) {
	Player* player = xmalloc(sizeof(Player));
	if (!player) {
		abort();
	}
	player->health = health;
	player->effects = NULL;
	player->pos.x = 0;
	player->pos.y = 0;
	player->state = STATE_IN_AIR;
	return player;
}

Map* make_map(Vector2 player_start) {
	Map* map = xmalloc(sizeof(Map));
	map->platforms = (PlatformDA*)xmalloc(sizeof(PlatformDA));
	map->platforms->items = NULL;
	map->platforms->count = 0;
	map->platforms->size = 0;
	map->player_start = player_start;
	return map;
}

void map_free(Map* map) {
	da_free(map->platforms);
	free(map->platforms);
	free(map);
}

Platform* make_platform(float x, float y, float w, float h, Looks look) {
	Platform* platform = xmalloc(sizeof(Platform));
	platform->pos = (Rectangle){.x=x, .y=y, .width=w, .height=h};
	platform->look = look;
	return platform;
}

static inline void draw_map(Map* map) {
	BeginDrawing();
	ClearBackground(BLACK);
	DrawTextureRec(player_tex, (Rectangle){
			.x=0,
			.y=0,
			.width=10,
			.height=50
		}, player.pos, WHITE);
	for (typeof(map->platforms->count) i=0; i<map->platforms->count; ++i) {
		DrawRectangleRec(map->platforms->items[i]->pos, map->platforms->items[i]->look.looks.color);
	}
	EndDrawing();
}

static inline void apply_player_physics(Map* map) {
	if (player.state == STATE_ON_SOMETHING) {
		if (player.current_platform && !CheckCollisionRecs(GET_PLAYER_REC((&player)), player.current_platform->pos)) {
			player.state = STATE_IN_AIR;
			player.current_platform = NULL;
		}
		return;
	}
	for (uint32_t i=0; i<map->platforms->count; ++i) {
		if (!CheckCollisionRecs(GET_PLAYER_REC((&player)), map->platforms->items[i]->pos)) {
			player.pos.y += GRAV;
		} else {
			player.current_platform = map->platforms->items[i];
			player.state = STATE_ON_SOMETHING;
		}
	}
}

static inline bool player_collides(Player* player, Map* map) {
	for (uint32_t i=0; i<map->platforms->count; ++i) {
		if (!CheckCollisionRecs(GET_PLAYER_REC((player)), map->platforms->items[i]->pos)) {
			return true;
		}
	}
	return false;
}

static inline bool rectangle_collides(Rectangle rect, Map* map) {
	for (uint32_t i=0; i<map->platforms->count; ++i) {
		if (!CheckCollisionRecs(rect, map->platforms->items[i]->pos)) 
			return true;
	}
	return false;
}

// Proper collision check
// * Different checks for horizontal and vertical collision
// * Keep track of player state
// * Abort movement if it requires passing through a solid object

// TODO: add proper collision
static inline void move_player_relative(Map* map, Player* player, Vector2 new_pos) {
	player->pos.y += new_pos.y;
	player->pos.x += new_pos.x;

	// float old_x=player->pos.x, old_y=player->pos.y;
	// player->pos.x += new_pos.x;
	// if (rectangle_collides((Rectangle){.x=player->pos.x+new_pos.x, .y=player->pos.y+new_pos.y-5, .width=10, .height=50}, map)) {
	// 	player->pos.x = old_x;
	// }
	// player->pos.y += new_pos.y;
	// if (rectangle_collides((Rectangle){.x=player->pos.x, .y=player->pos.y-5, .width=10, .height=50}, map)) {
	// 	player->pos.y = old_y;
	// }
}

int main() {
	InitWindow(600, 300, "Game :D");

	SetTargetFPS(30);

	Player* loc_player = make_player(UINT16_MAX);
	memcpy(&player, loc_player, sizeof(Player));
	free(loc_player);

	Rectangle platform = (Rectangle){
		.x=300,
		.y=150,
		.width=50,
		.height=10
	};

	player_tex = LoadTexture("./wall.png");

	Map* global = make_map((Vector2){.x=300.0, .y=130.0});
	da_append(global->platforms, make_platform(300, 150, 70, 10, (Looks){.is_texture=0, .looks.color=RED}));
	da_append(global->platforms, make_platform(0, 150, 70, 10, (Looks){.is_texture=0, .looks.color=WHITE}));
	da_append(global->platforms, make_platform(70, 170, 70, 10, (Looks){.is_texture=0, .looks.color=WHITE}));
	da_append(global->platforms, make_platform(140, 190, 70, 10, (Looks){.is_texture=0, .looks.color=WHITE}));
	da_append(global->platforms, make_platform(210, 210, 70, 10, (Looks){.is_texture=0, .looks.color=WHITE}));

	while (!WindowShouldClose()) {
		draw_map(global);

		if (IsKeyDown(KEY_D)) move_player_relative(global, &player, (Vector2){PLAYER_SPEED, 0});
		if (IsKeyDown(KEY_A)) move_player_relative(global, &player, (Vector2){-PLAYER_SPEED, 0});
		if (IsKeyDown(KEY_W) && player.state == STATE_ON_SOMETHING) {
			move_player_relative(global, &player, (Vector2){0, -JUMP_POW});
			player.state = STATE_IN_AIR;
		}
		apply_player_physics(global);
	}

	map_free(global);

	CloseWindow();
}