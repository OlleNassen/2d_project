#ifndef GAME_H
#define GAME_H
#include "camera.h"
#include "tilemap.h"

struct Game
{
	Camera camera;
	Tilemap tilemap;

	unsigned int shader;
};

void game_initialize(Game& game);
void game_start(Game& game);
void game_update(Game& game);
void game_render(Game& game);

#endif