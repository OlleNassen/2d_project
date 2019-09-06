#include "game.h"
#include "SDL/SDL.h"

#define PI 3.14159

void game_initialize(Game & game)
{
	cameraInitializeDefault(game.camera);
	drawer_initialize(game.drawer);
}

void game_start(Game& game)
{

}

void game_update(Game& game)
{

}

void game_draw(Game& game)
{
	drawer_draw(game.drawer, game.camera);
}