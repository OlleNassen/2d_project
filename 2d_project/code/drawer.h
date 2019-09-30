#ifndef DRAWER_H
#define DRAWER_H
#include "render_data.h"
#include "camera.h"
#include <SDL/SDL.h>
#include "math2d.h"

typedef Vector2 Quad[4];

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct Vertex
{
	Vector2 position;
};

struct Drawer
{
	unsigned int the_one_shader;
	Texture the_one_texture;

	Vector2* sprites_world_positions;
	Quad* vertex_local_coords;
	Quad* vertex_tex_coords;
	Color* vertex_colors;
	unsigned short* vertex_indices;

	unsigned short total_num_indices;
	unsigned short total_num_vertices;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int ssbo;

	Vertex *vertices;
};

void drawer_initialize(Drawer& drawer, const Uint32* type_data, unsigned short num_tiles_rows, unsigned short num_tiles_columns);
void drawer_draw_combat(Drawer& drawer, Camera& camera, Vector2 team_positions[], short team_classes[], Vector2& cursor_pos, Uint32 *path);
void drawer_draw_build(Drawer& drawer, Camera& camera, char* names[4]);
void drawer_draw_mainmenu(Drawer& drawer, Camera& camera);
void text_render(Drawer& drawer, const char* text, unsigned short num_letters);

#endif