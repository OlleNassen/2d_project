#ifndef TILEMAP_H
#define TILEMAP_H

struct Tilemap
{
	unsigned int num_tiles_x;
	unsigned int num_tiles_y;

	unsigned int tile_size_x;
	unsigned int tile_size_y;

	char* type;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
};

void tilemap_draw(Tilemap& tilemap);
void tilemap_generate(Tilemap& tilemap, unsigned int num_tiles_x, unsigned int num_tiles_y, unsigned int tile_size_x, unsigned int tile_size_y);

#endif