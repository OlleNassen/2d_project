#include "game.h"
#include "shader.h"
#include "glad/glad.h"

#define PI 3.14159

void initializeLine(Line& line, const glm::vec2& startingPoint, float angle, const glm::vec3& color)
{
	line.thickness = 5.f;
	line.angle = angle;
	line.angle *= (float)PI / 180.f;
	line.speed = 1.f;
	line.color = color;
	line.lastPosition = startingPoint;
	line.alive = true;
}

void addToLine(Line& line, const glm::vec2& offset)
{
	glm::vec2 newPoint = line.lastPosition + offset;
	glm::vec2 newLine{ newPoint - line.lastPosition };
	glm::vec2 normal = { -newLine.y, newLine.x };
	normal /= sqrt(normal.x * normal.x + normal.y * normal.y);
	normal *= line.thickness;
	glm::vec2 nextSegment[4];
	nextSegment[0] = line.lastPosition + normal;
	nextSegment[1] = line.lastPosition - normal;
	nextSegment[2] = newPoint + normal;
	nextSegment[3] = newPoint - normal;

	for (int i = 0; i < 4; ++i)
		line.positions.emplace_back(nextSegment[i]);

	line.lastPosition = newPoint;
}

void updateCollision(Game& game)
{
	for (int i = 0; i < game.numPlayers; ++i)
	{
		if (game.lines[i].alive)
		{
			for (int j = 1; j < game.numPlayers - 1; ++j)
			{
				for (int k = 0; k < game.lines[j].positions.size() / 4; k+=4)
				{
					glm::vec2 m = game.lines[i].lastPosition;
					glm::vec2 a = game.lines[j].positions[k];
					glm::vec2 b = game.lines[j].positions[k+1];
					glm::vec2 d = game.lines[j].positions[k+3];

					glm::vec2 AM = m - a;
					glm::vec2 AB = b - a;
					glm::vec2 AD = d - a;

					float AMdotAB = AM.x * AB.x + AM.y * AB.y;
					float ABdotAB = AB.x * AB.x + AB.y * AB.y;
					float AMdotAD = AM.x * AD.x + AM.y * AD.y;
					float ADdotAD = AD.x * AD.x + AD.y * AD.y;

					if ((0 < AMdotAB < ABdotAB) ^ (0 < AMdotAD < ADdotAD))
					{
						game.lines[i].alive = false;
					}
				}
			}
		}
	}
}

void updateMovement(Game& game)
{
	for (unsigned int i = 0; i < game.numPlayers; ++i)
	{
		if (game.lines[i].alive)
		{
			float x = cos(game.lines[i].angle) * game.lines[i].speed;
			float y = sin(game.lines[i].angle) * game.lines[i].speed;

			addToLine(game.lines[i], {x,y});

			glBindBuffer(GL_ARRAY_BUFFER, game.vbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * game.lines[i].positions.size(), &game.lines[i].positions[0], GL_STATIC_DRAW);
		}
	}
}

void clearPlayers(Game& game)
{
	for (unsigned int i = 0; i < game.numPlayers; ++i)
	{
		game.lines[i].positions.clear();
		glBindBuffer(GL_ARRAY_BUFFER, game.vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);
	}
}

glm::vec2 resetPosition(Game& game, int indexedPlayer)
{
	glm::vec2 newPos = glm::vec2(rand() % 1280, rand() % 720);
	int i = 0;
	for (i; i < indexedPlayer; ++i)
	{
		glm::vec2 temp = newPos - game.lines[i].lastPosition;
		float length = sqrt(temp.x * temp.x + temp.y * temp.y);
		if (length < 20.f)
		{
			newPos = glm::vec2(rand() % 1280, rand() % 720);
			i = 0;
		}
	}
	return newPos;
}

void gameInitialize(Game& game)
{
	game.vao = 0;
	game.shader = 0;
	game.numPlayers = 0;
	game.vbo = nullptr;
	game.lines = nullptr;
}

void gameStart(Game& game, int numPlayers)
{
	if (game.vao == 0)
	{
		glGenVertexArrays(1, &game.vao);
		glBindVertexArray(game.vao);
		game.shader = shaderCreate("resources/shaders/2d.vert", "resources/shaders/2d.frag");
		cameraInitializeDefault(game.camera);
	}

	game.numPlayers = numPlayers;
	game.vbo = new unsigned int[numPlayers];
	game.lines = new Line[numPlayers];

	for (int i = 0; i < numPlayers; ++i)
	{
		initializeLine(game.lines[i], resetPosition(game, i), rand() % 360, glm::vec3(rand() % 255,rand() % 255, rand() % 255));

		glGenBuffers(1, &game.vbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, game.vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	}
}

void gameClearMemory(Game& game)
{
	for(unsigned int i = 0; i < game.numPlayers; ++i)
		glDeleteBuffers(1, &game.vbo[i]);
	delete[] game.vbo;
	delete[] game.lines;
}

void gameUpdate(Game& game)
{
	updateCollision(game);
	updateMovement(game);
}

void gameRender(Game& game)
{
	glBindVertexArray(game.vao);
	glUseProgram(game.shader);
	shaderUniform(game.shader, "view", cameraGetViewMatrix(game.camera));
	shaderUniform(game.shader, "projection", game.camera.ortho);
	for (unsigned int i = 0; i < game.numPlayers; ++i)
	{
		glBindBuffer(GL_ARRAY_BUFFER, game.vbo[i]);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
		shaderUniform(game.shader, "color", game.lines[i].color);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)game.lines[i].positions.size());
	}
}