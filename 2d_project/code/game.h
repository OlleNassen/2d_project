#ifndef GAME_H
#define GAME_H
#include "camera.h"

struct Tilemap
{
	int xy[16][16];
	unsigned int vbo;
	int size_x;
	int size_y;
};

struct Game
{
	unsigned int globalVao;
	Tilemap tilemap;
	Camera camera;

	unsigned int shader;
};

void gameInitialize(Game& game);
void gameStart(Game& game);
void gameUpdate(Game& game);
void gameRender(Game& game);

#endif