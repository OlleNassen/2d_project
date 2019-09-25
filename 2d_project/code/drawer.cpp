#include "drawer.h"
#include "shader.h"
#include <glad/glad.h>
#include "window.h"

void drawer_initialize(Drawer& drawer, const Uint32* type_data, unsigned short num_tiles_rows, unsigned short num_tiles_columns)
{
	drawer.shader_tex = shader_create("resources/shaders/2dtex.vert", "resources/shaders/2dtex.frag");

	glGenVertexArrays(1, &drawer.sprite_vao);
	glBindVertexArray(drawer.sprite_vao);
	glGenBuffers(1, &drawer.sprite_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, drawer.sprite_vbo);
	glBufferData(GL_ARRAY_BUFFER, 128, 0, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	float *pointer = 0;
	unsigned int stride = sizeof(float) * 4;
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, pointer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, pointer + 2);

	unsigned short* indices = new unsigned short[6*4];
	for (int i = 0; i < 4*6; i+=6)
	{
		indices[i+0] = i+0;
		indices[i+1] = i+1;
		indices[i+2] = i+2;
		indices[i+3] = i+0;
		indices[i+4] = i+2;
		indices[i+5] = i+3;
	}

	glGenBuffers(1, &drawer.sprite_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawer.sprite_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 4*6, &indices[0], GL_STATIC_DRAW);

	drawer.tilemap_texture = texture_from_file("tiles.png");
	drawer.cursor_texture = texture_from_file("cursor.png");
	drawer.player_texture = texture_from_file("spritesheet.png");

	tilemap_generate(drawer.tilemap, type_data, drawer.tilemap_texture.width, drawer.tilemap_texture.height, num_tiles_rows, num_tiles_columns, 32, 32);

	GLenum flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
	unsigned int size = 1024 * 1024;
	glGenBuffers(1, &drawer.sprite_storage);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, drawer.sprite_storage);
	glBufferStorage(GL_SHADER_STORAGE_BUFFER, size, 0, flags);
	drawer.vertices = (Vertex *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size, flags);
}

void drawer_draw_combat(Drawer& drawer, Camera& camera, Vector2 team_positions[], short team_classes[], Vector2& cursor_pos, Uint32 *path)
{
	glUseProgram(drawer.shader_tex);
	shader_uniform(drawer.shader_tex, "view", vector2_create(camera.position.x, camera.position.y));
	shader_uniform(drawer.shader_tex, "projection", camera.ortho);
	shader_uniform(drawer.shader_tex, "sprite_tex", 0);
	shader_uniform(drawer.shader_tex, "num_vertices", (int)drawer.tilemap.num_indices);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, drawer.tilemap_texture.id);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, drawer.tilemap.ssbo);
	tilemap_draw(drawer.tilemap);

	glBindVertexArray(drawer.sprite_vao);
	glBindBuffer(GL_ARRAY_BUFFER, drawer.sprite_vbo);
	Rect rect;
	SpriteAnimation anim;
	float time = window_time_get();
	rect = rect_createfv(vector2_create(cursor_pos.x + 16, cursor_pos.y + 16), 32, 32);

	anim.speed = 0.5f;
	anim.sprite = rect_create(0, 0, 32, 32);
	anim.size = rect_create(0, 0, 32 * 2, 32);
	glDisable(GL_DEPTH_TEST);
	/*sprite_draw(&rect, &anim, &drawer.cursor_texture, time);

	for (int i = 0; i < 40 * 60; ++i)
	{
		int x = i % 60;
		int y = i / 60;
		
		if (path[i] < 5)
		{
			rect = rect_createfv(vector2_create(x * 32+16, y * 32+16), 32, 32);
			anim.speed = 0.5f;
			anim.sprite = rect_create(0, 0, 32, 32);
			anim.size = rect_create(0, 0, 32 * 2, 32);
			sprite_draw(&rect, &anim, &drawer.cursor_texture, time);
		}
	}*/
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < 4; ++i)
	{
		/*rect = rect_createfv(vector2_create(team_positions[i].x+16, team_positions[i].y+16), 32, 32);
		anim.speed = 0.5f;
		anim.sprite = rect_create(team_classes[i] * 4 * 32, 0, 32,     32);
		anim.size =   rect_create(team_classes[i] * 4 * 32, 0, 32, 32);
		glDisable(GL_DEPTH_TEST);
		sprite_draw(&rect, &anim, &drawer.player_texture, time); */
		drawer.vertices[i].position = team_positions[i];
	}
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, drawer.sprite_storage);
	glDrawElements(GL_TRIANGLES, 4 * 6, GL_UNSIGNED_SHORT, 0);

}

void drawer_draw_build(Drawer & drawer, Camera & camera, char* names[4])
{
	Rect rect = rect_create(camera.position.x + 1280 / 2, camera.position.y + 720 / 2, 1280, 720);
	SpriteAnimation anim;
	anim.speed = 0.5f;
	anim.sprite = rect_create(0, 0, 32, 32);
	anim.size = rect_create(0, 0, 24 * 3, 32);

	float time = window_time_get();
	glDisable(GL_DEPTH_TEST);
	sprite_draw(&rect, &anim, &drawer.player_texture, time);
	glEnable(GL_DEPTH_TEST);
}

void drawer_draw_mainmenu(Drawer & drawer, Camera & camera)
{

}
