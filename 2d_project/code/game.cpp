#include "game.h"
#include "shader.h"
#include "glad/glad.h"
#include "math2d.h"

struct Quad
{
	Vector2 abcd[4] = 
	{
		vector2(-0.5f, -0.5f),
		vector2(0.5f, -0.5f),
		vector2(0.5f, 0.5f),
		vector2(-0.5f, 0.5f)
	};
};

#define PI 3.14159

void game_initialize(Game & game)
{
	game.tilemap.size_x = 1280 / 16;
	game.tilemap.size_y = 720 / 16;
	game.shader = shaderCreate("resources/shaders/2d.vert", "resources/shaders/2d.frag");
	glGenVertexArrays(1, &game.global_vao);
	glBindVertexArray(game.global_vao);

	glGenBuffers(1, &game.tilemap.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, game.tilemap.vbo);
	Quad vertexData[16][16];
	unsigned int indices[16 * 16 * 6];
	int offset = 0;
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			game.tilemap.xy[j][i] = '-1';
			vertexData[j][i].abcd[0] = vector2_add(vertexData[j][i].abcd[0], vector2(j * game.tilemap.size_x, i * game.tilemap.size_y));
			vertexData[j][i].abcd[1] = vector2_add(vertexData[j][i].abcd[1], vector2(j * game.tilemap.size_x, i * game.tilemap.size_y));
			vertexData[j][i].abcd[2] = vector2_add(vertexData[j][i].abcd[2], vector2(j * game.tilemap.size_x, i * game.tilemap.size_y));
			vertexData[j][i].abcd[3] = vector2_add(vertexData[j][i].abcd[3], vector2(j * game.tilemap.size_x, i * game.tilemap.size_y));

			indices[offset+0] = offset + 0;
			indices[offset+1] = offset + 1;
			indices[offset+2] = offset + 2;
			indices[offset+3] = offset + 0;
			indices[offset+4] = offset + 2;
			indices[offset+5] = offset + 3;

			offset += 6;
		}
	}
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Quad) * 16 * 16, &vertexData[0][0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glGenBuffers(1, &game.tilemap.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, game.tilemap.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 16 * 16 * 6, &indices[0], GL_STATIC_DRAW);

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
	glDrawElements(GL_TRIANGLES, 16 * 16 * 6, GL_UNSIGNED_INT, 0);
}