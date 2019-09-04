#include "game.h"
#include "shader.h"
#include "math2d.h"
#include "glad/glad.h"

#define PI 3.14159

void game_initialize(Game & game)
{
	game.shader = shaderCreate("resources/shaders/2d.vert", "resources/shaders/2d.frag");
	tilemap_generate(game.tilemap, 64, 32, 32, 32);
	cameraInitializeDefault(game.camera);
}

void game_start(Game& game)
{

}

void game_update(Game& game)
{

}

void game_render(Game& game)
{
	glUseProgram(game.shader);
	shaderUniform(game.shader, "view", cameraGetViewMatrix(game.camera));
	shaderUniform(game.shader, "projection", game.camera.ortho);
	tilemap_draw(game.tilemap);
}