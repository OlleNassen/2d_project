#include "render_data.h"
#include <glad/glad.h>
#include "math2d.h"

typedef struct
{
	float x;
	float y;
	float u;
	float v;
} SpriteVertex;

void sprite_draw(Rect *rect, SpriteAnimation *anim, Texture *text, float time)
{
	SpriteVertex vertices[4];
	vertices[0].x = rect->x + rect->w * 0.5f;
	vertices[0].y = rect->y - rect->h * 0.5f;

	vertices[1].x = rect->x - rect->w * 0.5f;
	vertices[1].y = rect->y - rect->h * 0.5f;

	vertices[2].x = rect->x + rect->w * 0.5f;
	vertices[2].y = rect->y + rect->h * 0.5f;

	vertices[3].x = rect->x - rect->w * 0.5f;
	vertices[3].y = rect->y + rect->h * 0.5f;

	int width = anim->size.w / anim->sprite.w;
	int height = anim->size.h / anim->sprite.h;
	int frame = (int)(time / anim->speed) % (width * height);

	int x = frame % width;
	int y = frame / width;

	Rect uv;
	uv.x = anim->sprite.x / text->width;
	uv.y = anim->sprite.y / text->height;
	uv.w = anim->sprite.w / text->width;
	uv.h = anim->sprite.h / text->height;

	vertices[0].u = x * uv.w + uv.x + uv.w;
	vertices[0].v = y * uv.h + uv.y + uv.h;

	vertices[1].u = x * uv.w + uv.x;
	vertices[1].v = y * uv.h + uv.y + uv.h;

	vertices[2].u = x * uv.w + uv.x + uv.w;
	vertices[2].v = y * uv.h + uv.y;

	vertices[3].u = x * uv.w + uv.x;
	vertices[3].v = y * uv.h + uv.y;

	/*vertices[0].u = anim->sprite.x + anim->sprite.w;
	vertices[0].v = anim->sprite.y;

	vertices[1].u = anim->sprite.x;
	vertices[1].v = anim->sprite.y;

	vertices[2].u = anim->sprite.x + anim->sprite.w;
	vertices[2].v = anim->sprite.y + anim->sprite.h;

	vertices[3].u = anim->sprite.x;
	vertices[3].v = anim->sprite.y + anim->sprite.h;*/

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, text->id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}