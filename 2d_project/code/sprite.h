#ifndef SPRITE_H
#define SPRITE_H

#include "math2d.h"

typedef struct
{
	Vector2 position;
	Vector2 size;
	unsigned int texture;
} Sprite;


void sprite_move(Sprite *sprite, float x, float y); 
void sprite_resize(Sprite *sprite, float x, float y);
void sprite_draw(Sprite *sprite);


#endif