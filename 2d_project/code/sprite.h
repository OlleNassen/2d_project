#ifndef SPRITE_H
#define SPRITE_H
#include "texture.h"
#include "math2d.h"

typedef struct
{
	Rect sprite;
	Rect size;
	float speed;
} SpriteAnimation;

void sprite_draw(Rect *rect, SpriteAnimation *anim, Texture *text, float time);

#endif