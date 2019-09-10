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
	srand(time(0));
}

void game_update(Game& game)
{
	camera_update(&game.camera);

	if (window_mouse_pressed(SDL_BUTTON_LEFT).pressed)
	{
		Vector2 mouse_pos = vector2_create(game.camera.mx, game.camera.my);
		game.player.position = mouse_pos;
	}
}

void game_draw(Game& game)
{
	drawer_draw(game.drawer, game.camera, &game.player.position);
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