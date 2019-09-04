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
	game.shader_tex = shaderCreate("resources/shaders/2dtex.vert", "resources/shaders/2dtex.frag");
	tilemap_generate(game.tilemap, 64, 32, 32, 32);
	cameraInitializeDefault(game.camera);
	
	glGenVertexArrays(1, &game.spriteVAO);
	glBindVertexArray(game.spriteVAO);
	glGenBuffers(1, &game.spriteVBO);
	glBindBuffer(GL_ARRAY_BUFFER, game.spriteVBO);
	glBufferData(GL_ARRAY_BUFFER, 128, 0, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	float *pointer = 0;
	unsigned int stride = sizeof(float) * 4;
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, pointer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, pointer + 2);
	
	game.texture = texture_from_file("test.png");
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

	Rect rect = rect_create(150, 150, 200, 200);
	SpriteAnimation anim;
	anim.speed = 0.5f;
	anim.sprite = rect_create(0, 0, 24, 32);
	anim.size = rect_create(0, 0, 24 * 3, 32);

	glUseProgram(game.shader_tex);
	glBindVertexArray(game.spriteVAO);
	glBindBuffer(GL_ARRAY_BUFFER, game.spriteVBO);

	shaderUniform(game.shader_tex, "view", vector2_create(game.camera.position.x, game.camera.position.y));
	shaderUniform(game.shader_tex, "projection", game.camera.ortho);
	shaderUniform(game.shader_tex, "sprite_tex", 0);

	float time = window_time_get();
	sprite_draw(&rect, &anim, &game.texture, time);
}