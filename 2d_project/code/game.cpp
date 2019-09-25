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

void shortest_path(Uint32 *path, Uint32 *grid, Uint32 width, Uint32 height, Uint32 x, Uint32 y)
{
	int i = 0;
	while (grid[x + y * width] > 1)
	{		
		Uint32 posx = (x + 1) < width  ? grid[(x + 1) + y * width] : 1000;
		Uint32 negx = (x - 1) < width  ? grid[(x - 1) + y * width] : 1000;
		Uint32 posy = (y + 1) < height ? grid[x + (y + 1) * width] : 1000;
		Uint32 negy = (y - 1) < height ? grid[x + (y - 1) * width] : 1000;
		
		x = posx < negx ? posx : negx;
		y = posy < negy ? posy : negy;

		path[i++] = x + y * width;
	}
}

void flood(Uint32 *path, Uint32 *tiles, Uint32 width, Uint32 height, Uint32 x, Uint32 y, Uint32 mov)
{
	if (x < width && y < height && (mov + tiles[x + y * width]) < path[x + y * width])
	{
		mov += tiles[x + y * width];
		path[x + y * width] = mov;

		flood(path, tiles, width, height, x + 1, y, mov);
		flood(path, tiles, width, height, x - 1, y, mov);
		flood(path, tiles, width, height, x, y + 1, mov);
		flood(path, tiles, width, height, x, y - 1, mov);
	}
}

void create_game_map(GameMap& gameMap);
void generate_character(Game& game, int index);
char* generate_name(Game& game);
short generate_class(Game& game);
short generate_proficiency(Game& game);
void load_names_from_file(Game& game, const char* path);

void game_initialize(Game& game)
{
	srand(time(0));
	game.current_state = StateCombat;
	Uint32 tiles[16];
	for (int i = 0; i < 16; ++i) tiles[i] = 1;
	Uint32 path[16];
	for (int i = 0; i < 16; ++i) path[i] = 1000;
	
	flood(path, tiles, 4, 4, 2, 2, 0);

	printf("%u %u %u %u\n", path[0], path[1], path[2], path[3]);
	printf("%u %u %u %u\n", path[4], path[5], path[6], path[7]);
	printf("%u %u %u %u\n", path[8], path[9], path[10], path[11]);
	printf("%u %u %u %u\n", path[12], path[13], path[14], path[15]);
	
	create_game_map(game.map);
	camera_initialize_default(game.camera);
	drawer_initialize(game.drawer, game.map.tiles, game.map.height, game.map.width);
	load_names_from_file(game, "names.bin");
	for(int i = 0; i < 4; ++i)
		generate_character(game, i);

	Uint32 *ptr = (Uint32 *)malloc(sizeof(Uint32) * game.map.size * 4);
	for (int i = 0; i < game.map.size * 4; ++i) ptr[i] = 1000;
	game.team_data.paths[0] = ptr;
	game.team_data.paths[1] = ptr + game.map.size;
	game.team_data.paths[2] = ptr + game.map.size * 2;
	game.team_data.paths[3] = ptr + game.map.size * 3;
}

void game_update(Game& game)
{
	camera_update(&game.camera);
	
	GameButton up = window_keyboard_pressed(SDLK_i);
	GameButton left = window_keyboard_pressed(SDLK_j);
	GameButton down = window_keyboard_pressed(SDLK_k);
	GameButton right = window_keyboard_pressed(SDLK_l);
	GameButton select = window_mouse_pressed(SDL_BUTTON_LEFT);

	if(window_keyboard_pressed(SDLK_1).pressed)
		game.current_state = StateMainMenu;
	if (window_keyboard_pressed(SDLK_2).pressed)
		game.current_state = StateBuild;
	if (window_keyboard_pressed(SDLK_3).pressed)
		game.current_state = StateCombat;

	
	if (select.pressed && select.transitions > 0)
	{
		int w_w, w_h;
		window_size_get(&w_w, &w_h);
		int x, y;
		window_mouse_position(&x, &y);
		Vector2 result = vector2_create(-game.camera.position.x + x, -game.camera.position.y + (w_h - y));

		//result = dimetric_to_cart(result);

		result.x = (int)result.x;
		result.y = (int)result.y;

		result.x -= (int)result.x % 32;
		result.y -= (int)result.y % 32;

		game.cursor.position = result;

		for (int i = 0; i < 4; ++i)
		{
			flood(game.team_data.paths[i], 
				game.map.cost, game.map.width, game.map.height, 
				(Uint32)game.team_data.positions[i].x / 32, (Uint32)game.team_data.positions[i].y / 32, 0);
		}	
	}
}

void game_draw(Game& game)
{
	switch (game.current_state)
	{
	case StateBuild:
		drawer_draw_build(game.drawer, game.camera, game.team_data.names);
		break;
	case StateCombat:
		drawer_draw_combat(game.drawer, game.camera, game.team_data.positions, game.team_data.character_classes, game.cursor.position, game.team_data.paths[0]);
		break;
	case StateMainMenu:
		drawer_draw_mainmenu(game.drawer, game.camera);
		break;
	}
}

void create_game_map(GameMap& gameMap)
{
	gameMap.width = 60;
	gameMap.height = 40;
	gameMap.size = gameMap.width * gameMap.height;

	gameMap.tiles = (Uint32 *)malloc(sizeof(Uint32) * gameMap.size);

	for (int i = 0; i < gameMap.size; ++i)
	{
		int row = rand() % 7;
		row *= 8;
		row += rand() % 6;

		gameMap.tiles[i] = row;
	}

	gameMap.cost = (Uint32 *)malloc(sizeof(Uint32) * gameMap.size);

	for (int i = 0; i < gameMap.size; ++i)
	{
		gameMap.cost[i] = 1;
	}


	gameMap.pieces = (Piece **)malloc(sizeof(Piece *) * gameMap.size);
	memset(gameMap.pieces, 0, sizeof(Piece *) * gameMap.size);
}

void generate_character(Game& game, int index)
{
	game.team_data.names[index] = generate_name(game);
	game.team_data.character_classes[index] = generate_class(game);
	game.team_data.class_proficiencies[index] = generate_proficiency(game);
	int x_rand = rand() % game.map.width+1;
	int y_rand = rand() % game.map.height+1;
	game.team_data.positions[index] = vector2_create(32.f * x_rand,32.f* y_rand);
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
