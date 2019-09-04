#include "sprite.h"
#include <glad/glad.h>

typedef struct
{
	float x;
	float y;
} SpriteVertex;

void sprite_move(Sprite *sprite, float x, float y)
{

}

void sprite_resize(Sprite *sprite, float x, float y)
{

}

void sprite_draw(Sprite *sprite)
{
	SpriteVertex vertices[4];
	vertices[0].x = sprite->position.x - sprite->size.x * 0.5f;
	vertices[0].y = sprite->position.y - sprite->size.y * 0.5f;

	vertices[1].x = sprite->position.x + sprite->size.x * 0.5f;
	vertices[1].y = sprite->position.y - sprite->size.y * 0.5f;

	vertices[2].x = sprite->position.x - sprite->size.x * 0.5f;
	vertices[2].y = sprite->position.y + sprite->size.y * 0.5f;

	vertices[3].x = sprite->position.x + sprite->size.x * 0.5f;
	vertices[3].y = sprite->position.y + sprite->size.y * 0.5f;


	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}