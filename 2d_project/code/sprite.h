#ifndef SPRITE_H
#define SPRITE_H

#include "math2d.h"

typedef struct
{
	float width;
	float height;
} Texture;

typedef struct 
{
	float x;
	float y;
	float w;
	float h;
} Rectangles;

typedef struct
{
	Rectangles animations[16];
	
	Rectangles size;
	Vector2 position;
	Vector2 sizee;
	unsigned int texture;
} Sprite;

void sprite_draw(Sprite *sprite);

void sprite_draw(Sprite *sprite, int animation, int frame);


#endif