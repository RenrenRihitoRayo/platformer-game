#include <raylib.h>
#include "raymath.h"
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "renplat.h"
#include "entity.h"
#include "assets.h"

GameState GAME;
float  SCREEN_WIDTH;
float  SCREEN_HEIGHT;

static inline void init_game (void)
{
	Texture2D psprite;
	InitWindow (600, 300, "Ren Platforming Program");
	SetTargetFPS (RENPLAT_GAMEFPS);

	SCREEN_WIDTH = (float) GetScreenWidth ();
	SCREEN_HEIGHT = (float) GetScreenHeight ();
	psprite =  LoadTexture (ASSETS_PLAYER_SPRITE);

	GAME.player = make_entity (
			"Player", psprite, 100,
			PLAYER_SPEED,
			(Vector2){.x=0, .y=0 },
			RENPLAT_PLAYER_WIDTH,
			RENPLAT_PLAYER_HEIGHT
	);

	GAME.camera = (Camera2D){
		.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f},
		.target = GAME.player->pos,
		.rotation = 0.0f,
		.zoom = 1.0f,
	};
}

static inline void cleanup_game (void)
{
	CloseWindow ();
}

static void update_player (float delta)
{
	if (IsKeyDown (KEY_D) || IsKeyDown (KEY_RIGHT))
		move_entity(GAME.player, (Vector2){1, 0}, delta);

	if (IsKeyDown (KEY_A) || IsKeyDown (KEY_LEFT))
		move_entity(GAME.player, (Vector2){-1, 0}, delta);

	if (IsKeyDown (KEY_SPACE))
		move_entity(GAME.player, (Vector2){0, -1}, delta);
}


#define RENPLAT_CAM_MIN_SPEED  30
#define RENPLAT_CAM_MIN_EFFECT 10
#define RENPLAT_CAM_FRACSPEED 0.8f

void update_cam (Camera2D *cam, Entity *e, float delta)
{
	float length;
	Vector2 diff;

	cam->offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
	diff = Vector2Subtract (e->pos, cam->target);
	length = Vector2Length (diff);

	if (length > RENPLAT_CAM_MIN_EFFECT)
	{
		float speed = fmaxf(RENPLAT_CAM_FRACSPEED*length, RENPLAT_CAM_MIN_SPEED);
		cam->target = Vector2Add(
						cam->target,
						Vector2Scale(diff, speed*delta/length)
		);
	}
}

int main()
{
	float dt;

	init_game ();
	while (!WindowShouldClose ())
	{
		dt =  (float) GetFrameTime ();
		SCREEN_WIDTH = (float) GetScreenWidth ();
		SCREEN_HEIGHT = (float) GetScreenHeight ();

		update_cam (&GAME.camera, GAME.player,  dt);
		update_player (dt);

		BeginDrawing ();

			ClearBackground (BLACK);

			BeginMode2D (GAME.camera);

				DrawTextureRec (
					GAME.player->sprite, get_entity_rect (GAME.player),
					GAME.player->pos, WHITE
				);

			EndMode2D ();

		EndDrawing ();
	}
	cleanup_game ();
	return 0;
}
