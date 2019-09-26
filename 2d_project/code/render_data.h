#ifndef RENDER_DATA_H
#define RENDER_DATA_H
#include "math2d.h"
#include "texture.h"

#include <SDL/SDL.h>

typedef struct
{
	Rect sprite;
	Rect size;
	float speed;
} SpriteAnimation;

void sprite_draw(Rect *rect, SpriteAnimation *anim, Texture *text, float time);
#endif