#include "game.h"
#include "window.h"
#include <SDL/SDL.h>
#include <memory.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PI 3.14159

typedef struct
{
	Uint32 cost;
} Tile;

void flood(Uint32 *path_grid, Tile *tiles, Uint32 width, Uint32 height, Uint32 x, Uint32 y, Uint32 mov)
{
	if (x < width && y < height && mov < path_grid[x * y])
	{
		mov += tiles[x * y].cost;
		path_grid[x * y] = mov;

		flood(path_grid, tiles, width, height, x + 1, y, mov);
		flood(path_grid, tiles, width, height, x - 1, y, mov);
		flood(path_grid, tiles, width, height, x, y + 1, mov);
		flood(path_grid, tiles, width, height, x, y - 1, mov);
	}
}

void create_game_map(GameMap& gameMap);
void generate_character(Game& game);
char* generate_name(Game& game);
short generate_class(Game& game);
short generate_proficiency(Game& game);
void load_names_from_file(Game& game, const char* path);

void game_initialize(Game& game)
{
	create_game_map(game.map);
	camera_initialize_default(game.camera);
	drawer_initialize(game.drawer, game.map.tiles, game.map.num_tiles_rows, game.map.num_tiles_columns);
	game.player.position.x = 32 * 4;
	game.player.position.y = 32 * 4;
	srand(time(0));
	load_names_from_file(game, "names.bin");
	generate_character(game);
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

		result.x = (int)result.x;
		result.y = (int)result.y;

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

void generate_character(Game& game)
{
	game.player.name = generate_name(game);
	game.player.character_class = (CharacterClass)generate_class(game);
	game.player.class_proficiency = generate_proficiency(game);
}

char* generate_name(Game & game)
{
	short new_line = rand() % 100000;

	while (game.names[new_line] % 100000 != '\n')
		new_line++;
	short temp = ++new_line;
	while (game.names[temp] % 100000 != '\n')
		temp++;

	short size = abs(temp - new_line) + 1;
	char* name = (char*)malloc(size);
	memset(name, 0, size);

	short index = 0;
	for (short i = new_line; i < temp; ++i)
		name[index++] += game.names[i];

	return name;
}

short generate_class(Game & game)
{
	return rand() % NumClasses;
}

short generate_proficiency(Game & game)
{
	return rand() % 5;
}

void load_names_from_file(Game& game, const char * path)
{
	FILE* f;
	fopen_s(&f, path, "rb");
	fseek(f, 0, SEEK_END);
	unsigned long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); // or frewind(f)
	game.names = (char*)malloc(fsize + 1);
	memset(game.names, 0, fsize+1);
	fread(game.names, 1, fsize, f);
	fclose(f);
}
