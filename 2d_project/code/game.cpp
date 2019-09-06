#include "game.h"
#include <SDL/SDL.h>
#include <memory.h>

#define PI 3.14159

void create_game_map(GameMap& gameMap);

void game_initialize(Game& game)
{
	create_game_map(game.map);
	camera_initialize_default(game.camera);
	drawer_initialize(game.drawer, game.map.num_tiles_rows, game.map.num_tiles_columns);
}

void game_update(Game& game)
{

}

void game_draw(Game& game)
{
	drawer_draw(game.drawer, game.camera);
}

void create_game_map(GameMap& gameMap)
{
	gameMap.num_tiles_rows = 20;
	gameMap.num_tiles_columns = 30;
	gameMap.tiles = new char[gameMap.num_tiles_rows * gameMap.num_tiles_columns];
	memset(gameMap.tiles, 0, sizeof(char) * gameMap.num_tiles_rows * gameMap.num_tiles_columns);
}