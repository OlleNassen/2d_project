#ifndef DRAWER_H
#define DRAWER_H
#include "render_data.h"
#include "camera.h"
#include <SDL/SDL.h>
#include "math2d.h"

typedef Vector2 Quad[4];

struct Vertex
{
	Vector2 position;
};

struct Drawer
{
	Texture the_one_texture;

	Vector2* sprites_world_positions;
	Quad* vertex_local_coords;
	Quad* vertex_tex_coords;
	unsigned short* vertex_indices;

	unsigned short total_num_indices;
	unsigned short total_num_vertices;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int ssbo;

	unsigned int sprite_storage;

	unsigned int shader;
	Vertex *vertices;
};

void drawer_initialize(Drawer& drawer, const Uint32* type_data, unsigned short num_tiles_rows, unsigned short num_tiles_columns);
void drawer_draw_combat(Drawer& drawer, Camera& camera, Vector2 team_positions[], short team_classes[], Vector2& cursor_pos, Uint32 *path);
void drawer_draw_build(Drawer& drawer, Camera& camera, char* names[4]);
void drawer_draw_mainmenu(Drawer& drawer, Camera& camera);
#endif