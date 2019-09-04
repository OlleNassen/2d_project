#include "game.h"
#include "shader.h"
#include "math2d.h"
#include "glad/glad.h"
#include "SDL/SDL.h"
#include "window.h"

#define PI 3.14159

void game_initialize(Game & game)
{
	game.shader = shaderCreate("resources/shaders/2d.vert", "resources/shaders/2d.frag");
	tilemap_generate(game.tilemap, 64, 32, 32, 32);
	cameraInitializeDefault(game.camera);
	
	glGenBuffers(1, &game.spriteVBO);
	glBufferData(GL_ARRAY_BUFFER, 128, 0, GL_STATIC_DRAW);
	game.texture = texture_from_file("path.here");
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
	shaderUniform(game.shader, "view", vector2_create(game.camera.position.x, game.camera.position.y));
	shaderUniform(game.shader, "projection", game.camera.ortho);
	tilemap_draw(game.tilemap);

	Rect rect = rect_create(5,5,5,5);
	SpriteAnimation anim;

	sprite_draw(&rect, &anim, &game.texture, 0.0f);
}