#ifndef TILEMAP_H
#define TILEMAP_H
#include "texture.h"
#include "math2d.h"
struct Tilemap
{
	unsigned short num_tiles_rows;
	unsigned short num_tiles_columns;

	unsigned int tile_size_x;
	unsigned int tile_size_y;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

	Texture texture;
};

void tilemap_draw(Tilemap& tilemap);
void tilemap_generate(Tilemap& tilemap, const char* type_data, unsigned short num_tiles_rows, unsigned short num_tiles_columns, unsigned int tile_size_x, unsigned int tile_size_y);
Vector2 screen_to_world(Vector2& v);
Vector2 world_to_screen(Vector2& v);
#endif