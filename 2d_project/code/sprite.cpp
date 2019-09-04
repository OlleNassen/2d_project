#include "sprite.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
	vertices[0].v = y * uv.h + uv.y;

	vertices[1].u = x * uv.w + uv.x;
	vertices[1].v = y * uv.h + uv.y;

	vertices[2].u = x * uv.w + uv.x + uv.w;
	vertices[2].v = y * uv.h + uv.y + uv.h;

	vertices[3].u = x * uv.w + uv.x;
	vertices[3].v = y * uv.h + uv.y + uv.h;

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


Texture texture_from_memory(const char *buffer)
{
	Texture text;
	text.id = 0;
	return text;
}

Texture texture_from_file(const char *path)
{
	Texture text;
	glGenTextures(1, &text.id);
	glBindTexture(GL_TEXTURE_2D, text.id);

	stbi_set_flip_vertically_on_load(true);

	int num_components;

	unsigned char* data = stbi_load(path, &text.width, &text.height, &num_components, 4);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text.width,
			text.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}
	return text;
}