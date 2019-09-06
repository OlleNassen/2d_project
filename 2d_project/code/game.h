#ifndef GAME_H
#define GAME_H
#include "camera.h"
#include "drawer.h"

struct Game
{
	Camera camera;
	Drawer drawer;
};

void game_initialize(Game& game);
void game_start(Game& game);
void game_update(Game& game);
void game_draw(Game& game);

#endif