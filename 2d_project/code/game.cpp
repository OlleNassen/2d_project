#include "game.h"
#include "shader.h"
#include "glad/glad.h"

#define PI 3.14159
#include <iostream>
void game_initialize(Game & game)
{
	game.tilemap.size_x = 1280 / 16;
	game.tilemap.size_y = 720 / 16;
	game.shader = shaderCreate("resources/shaders/2d.vert", "resources/shaders/2d.frag");
	glGenVertexArrays(1, &game.global_vao);
	glBindVertexArray(game.global_vao);
	glGenBuffers(1, &game.tilemap.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, game.tilemap.vbo);
	glm::vec2 vertexData[16][16];
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			game.tilemap.xy[j][i] = '-1';
			vertexData[j][i] = glm::vec2(j * game.tilemap.size_x, i * game.tilemap.size_y);
		}
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 16 * 16, &vertexData[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

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
	glBindVertexArray(game.global_vao);
	glUseProgram(game.shader);
	shaderUniform(game.shader, "view", cameraGetViewMatrix(game.camera));
	shaderUniform(game.shader, "projection", game.camera.ortho);
	glBindBuffer(GL_ARRAY_BUFFER, game.tilemap.vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glDrawArrays(GL_POINTS, 0, 16 * 16);
}