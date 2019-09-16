#ifndef DRAWER_H
#define DRAWER_H
#include "sprite.h"
#include "tilemap.h"
#include "camera.h"

struct Drawer
{
	Tilemap tilemap;

	Texture texture;
	Texture player_texture;
	unsigned int sprite_vao;
	unsigned int sprite_vbo;

	unsigned int shader;
	unsigned int shader_tex;
};

void drawer_initialize(Drawer& drawer, const char* type_data, unsigned short num_tiles_rows, unsigned short num_tiles_columns);
void drawer_draw_combat(Drawer& drawer, Camera& camera, Vector2 team_positions[], Vector2& cursor_pos);
void drawer_draw_build(Drawer& drawer, Camera& camera, char* names[4]);
void drawer_draw_mainmenu(Drawer& drawer, Camera& camera);
#endif