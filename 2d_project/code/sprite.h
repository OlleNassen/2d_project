#ifndef SPRITE_H
#define SPRITE_H

#include "math2d.h"

typedef struct
{
	Rect sprite;
	Rect size;
	float speed;
} SpriteAnimation;

typedef struct
{
	unsigned int id;
	int width;
	int height;
} Texture;

void sprite_draw(Rect *rect, SpriteAnimation *anim, Texture *text, float time);


Texture texture_from_memory(const char *buffer);
Texture texture_from_file(const char *path);


#endif