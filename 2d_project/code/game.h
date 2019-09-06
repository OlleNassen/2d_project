#ifndef GAME_H
#define GAME_H
#include "camera.h"
#include "drawer.h"

typedef struct
{
	unsigned short num_tiles_rows;
	unsigned short num_tiles_columns;
	char* tiles;
}GameMap;

struct Game
{
	Camera camera;
	Drawer drawer;
	GameMap map;
};

void game_initialize(Game& game);
void game_update(Game& game);
void game_draw(Game& game);

#endif