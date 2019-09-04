#ifndef GAME_H
#define GAME_H
#include "camera.h"
#include "tilemap.h"
#include "sprite.h"

struct Game
{
	Camera camera;
	Tilemap tilemap;

	Texture texture;

	unsigned int spriteVAO;
	unsigned int spriteVBO;

	unsigned int shader;
	unsigned int shader_tex;
};

void game_initialize(Game& game);
void game_start(Game& game);
void game_update(Game& game);
void game_render(Game& game);

#endif