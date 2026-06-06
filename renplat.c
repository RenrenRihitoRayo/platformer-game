#include <raylib.h>
#include <stdlib.h>
#include <stdint.h>

#include "renplat.h"
#include "entity.h"
#include "assets.h"

GameState GAME;

static void init_game (void)
{
	Texture2D psprite;
	InitWindow (600, 300, "Ren Platforming Program");
	SetTargetFPS(RENPLAT_GAMEFPS);

	psprite =  LoadTexture (ASSETS_PLAYER_SPRITE);

	GAME.player = make_entity ("Player", psprite, 100, 0, 0,
								RENPLAT_PLAYER_WIDTH,
								RENPLAT_PLAYER_HEIGHT);
}

static void cleanup_game (void)
{
	CloseWindow ();
}

static void draw_map(void)
{
/*TODO: Cool if there was a effect to clear background with gamestate color */
	BeginDrawing ();
		ClearBackground (BLACK);
		DrawTextureRec (
			GAME.player->sprite, get_entity_rect (GAME.player),
			GAME.player->pos, WHITE
		);
	EndDrawing ();
}

int main()
{
	init_game ();

	while (!WindowShouldClose ())
	{
		draw_map ();

/* XXX
		if (IsKeyDown(KEY_D))
			move_entity_relative(GAME.player, (Vector2){PLAYER_SPEED, 0});
		if (IsKeyDown(KEY_A))
			move_entity_relative(GAME.player, (Vector2){-PLAYER_SPEED, 0});
		if (IsKeyDown(KEY_W) && player.state == STATE_ON_SOMETHING) {
			move_entity_relative(GAME.player, (Vector2){0, -JUMP_POW});
			player.state = STATE_IN_AIR;
		}

		apply_physics();
*/
	}

	cleanup_game ();
}
