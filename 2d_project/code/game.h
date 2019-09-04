#ifndef GAME_H
#define GAME_H
#include "camera.h"

struct Game
{
	Camera camera;

	unsigned int shader;
};

void gameInitialize(Game& game);
void gameStart(Game& game);
void gameUpdate(Game& game);
void gameRender(Game& game);

#endif