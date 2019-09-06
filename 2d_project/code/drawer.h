#ifndef DRAWER_H
#define DRAWER_H
#include "sprite.h"
#include "tilemap.h"
#include "camera.h"

struct Drawer
{
	Tilemap tilemap;

	Texture texture;
	unsigned int sprite_vao;
	unsigned int sprite_vbo;

	unsigned int shader;
	unsigned int shader_tex;
};

void drawer_initialize(Drawer& drawer, unsigned short num_tiles_rows, unsigned short num_tiles_columns);
void drawer_draw(Drawer& drawer, Camera& camera);

#endif