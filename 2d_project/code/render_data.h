#ifndef RENDER_DATA_H
#define RENDER_DATA_H
#include "texture.h"
#include "math2d.h"
#include <SDL/SDL.h>

struct Tilemap
{
	unsigned short num_tiles_rows;
	unsigned short num_tiles_columns;

	unsigned int tile_size_x;
	unsigned int tile_size_y;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

	unsigned short num_indices;
};

typedef struct
{
	Rect sprite;
	Rect size;
	float speed;
} SpriteAnimation;

void sprite_draw(Rect *rect, SpriteAnimation *anim, Texture *text, float time);

void tilemap_draw(Tilemap& tilemap);
void tilemap_generate(Tilemap& tilemap, const Uint32* type_data, unsigned int texture_width, unsigned int texture_height, unsigned short num_tiles_rows, unsigned short num_tiles_columns, unsigned int tile_size_x, unsigned int tile_size_y);

#endif