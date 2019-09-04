#include "game.h"
#include "shader.h"
#include "glad/glad.h"

#define PI 3.14159

void gameInitialize(Game & game)
{
	game.tilemap.size_x = 1280 / 16;
	game.tilemap.size_y = 720 / 16;
	game.shader = shaderCreate("2d.vert", "2d.frag");
	glGenVertexArrays(1, &game.globalVao);
	glBindVertexArray(game.globalVao);
	glGenBuffers(1, &game.tilemap.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, game.tilemap.vbo);
	float vertexData[16 * 2][16 * 2];
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			game.tilemap.xy[j][i] = -1;
			vertexData[j][i] = j * game.tilemap.size_x;
			vertexData[j+1][i+1] = i * game.tilemap.size_x;
		}
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16 * 16 * 2, &vertexData[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
}

void gameStart(Game& game)
{

}

void gameUpdate(Game& game)
{

}

void gameRender(Game& game)
{
	for (int i = 0; i < 16 * 16; ++i)
	{

	}
}