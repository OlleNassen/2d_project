#ifndef GAME_H
#define GAME_H
#include "camera.h"

struct Tilemap
{
	char xy[16][16];
	unsigned int vbo;
	unsigned int ebo;
	int size_x;
	int size_y;
};

struct Game
{
	unsigned int global_vao;
	Tilemap tilemap;
	Camera camera;

	unsigned int shader;
};

void game_initialize(Game& game);
void game_start(Game& game);
void game_update(Game& game);
void game_render(Game& game);

#endif