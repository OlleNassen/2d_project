#include "game.h"
#include "window.h"
#include <SDL/SDL.h>
#include <memory.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PI 3.14159

void create_game_map(GameMap& gameMap);
void generate_character(CharacterData& character);

void game_initialize(Game& game)
{
	create_game_map(game.map);
	camera_initialize_default(game.camera);
	drawer_initialize(game.drawer, game.map.tiles, game.map.num_tiles_rows, game.map.num_tiles_columns);
	generate_character(game.player);
	game.player.position.x = 32 * 4;
	game.player.position.y = 32 * 4;
	srand(time(0));
}

void game_update(Game& game)
{
	camera_update(&game.camera);
	
	GameButton up = window_keyboard_pressed(SDLK_i);
	GameButton left = window_keyboard_pressed(SDLK_j);
	GameButton down = window_keyboard_pressed(SDLK_k);
	GameButton right = window_keyboard_pressed(SDLK_l);
	
	if (up.pressed && up.transitions > 0)
	{
		game.player.position.y = game.player.position.y + 32;
	}
	if (left.pressed && left.transitions > 0)
	{
		game.player.position.x = game.player.position.x - 32;
	}
	if (down.pressed && down.transitions > 0)
	{
		game.player.position.y = game.player.position.y - 32;
	}
	if (right.pressed && right.transitions > 0)
	{
		game.player.position.x = game.player.position.x + 32;
	}

	if (window_mouse_pressed(SDL_BUTTON_LEFT).pressed)
	{
		int w_w, w_h;
		window_size_get(&w_w, &w_h);
		int x, y;
		window_mouse_position(&x, &y);
		Vector2 result = vector2_create(-game.camera.position.x + x, -game.camera.position.y + (w_h - y));

		result = dimetric_to_cart(result);

		result.x -= (int)result.x % 32;
		result.y -= (int)result.y % 32;

		game.cursor.position = result;
	}
}

void game_draw(Game& game)
{
	drawer_draw(game.drawer, game.camera, game.player.position, game.cursor.position);
}

void create_game_map(GameMap& gameMap)
{
	gameMap.num_tiles_rows = 40;
	gameMap.num_tiles_columns = 60;
	gameMap.tiles = new char[gameMap.num_tiles_rows * gameMap.num_tiles_columns];
	for (int i = 0; i < gameMap.num_tiles_rows * gameMap.num_tiles_columns; ++i)
	{
		int row = rand() % 7;
		row *= 9;
		row += rand() % 6;

		gameMap.tiles[i] = row;
	}
}

void generate_character(CharacterData& character)
{
	FILE* f;
	char temp[7];
	temp[6] = 0;

	fopen_s(&f, "names.bin", "r");
	fread(temp, sizeof(char), 6, f);
	fclose(f);

	printf(temp);
}