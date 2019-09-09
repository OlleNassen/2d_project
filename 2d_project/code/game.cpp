#include "game.h"
#include <SDL/SDL.h>
#include <memory.h>
#include "window.h"

#define PI 3.14159

void create_game_map(GameMap& gameMap);

void game_initialize(Game& game)
{
	create_game_map(game.map);
	camera_initialize_default(game.camera);
	drawer_initialize(game.drawer, game.map.tiles, game.map.num_tiles_rows, game.map.num_tiles_columns);
}

void game_update(Game& game)
{
	camera_update(&game.camera);		

	if (window_mouse_pressed(SDL_BUTTON_LEFT).pressed)
	{

	}
}

void game_draw(Game& game)
{
	drawer_draw(game.drawer, game.camera);
}

void create_game_map(GameMap& gameMap)
{
	gameMap.num_tiles_rows = 40;
	gameMap.num_tiles_columns = 60;
	gameMap.tiles = new char[gameMap.num_tiles_rows * gameMap.num_tiles_columns];
	for (int i = 0; i < gameMap.num_tiles_rows * gameMap.num_tiles_columns; ++i)
	{
		i > 180? gameMap.tiles[i] = 0: gameMap.tiles[i] = 20;
	}
}