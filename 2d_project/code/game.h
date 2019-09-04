#ifndef GAME_H
#define GAME_H
#include "camera.h"
#include <vector>

struct Line
{
	std::vector<glm::vec2> positions;
	glm::vec2 lastPosition;
	glm::vec3 color;
	float thickness;
	float angle;
	float speed;
	bool alive;
};

struct Game
{
	unsigned int vao;
	unsigned int* vbo;
	unsigned int numPlayers;
	Line* lines;
	Camera camera;

	unsigned int shader;
};

void gameInitialize(Game& game);
void gameStart(Game& game, int numPlayers);
void gameClearMemory(Game& game);
void gameUpdate(Game& game);
void gameRender(Game& game);

#endif