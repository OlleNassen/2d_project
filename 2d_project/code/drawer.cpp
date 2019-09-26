#include "drawer.h"
#include "shader.h"
#include <glad/glad.h>
#include "window.h"

void generate_tilemap(Drawer& drawer, const Uint32* type_data, unsigned short height, unsigned short width, unsigned int tile_size_width, unsigned int tile_size_height);
void generate_actors(Drawer& drawer, int num_actors, unsigned short classes[]);
void generate_buffers(Drawer& drawer);

void drawer_initialize(Drawer& drawer, const Uint32* type_data, unsigned short num_tiles_rows, unsigned short num_tiles_columns)
{
	drawer.the_one_shader = shader_program_create("resources/shaders/2dtex.vert", "resources/shaders/2dtex.frag");
	drawer.the_one_texture = texture_from_file("all_sprites.png");

	unsigned int size = 1024 * 1024;
	drawer.sprites_world_positions = new Vector2[size];
	drawer.vertex_local_coords = new Quad[size];
	drawer.vertex_tex_coords = new Quad[size];
	drawer.vertex_colors = new Color[size];
	drawer.vertex_indices = new unsigned short[size * 6];
	drawer.total_num_indices = 0;
	drawer.total_num_vertices = 0;

	generate_tilemap(drawer, type_data, num_tiles_rows, num_tiles_columns, 32, 32);
	unsigned short temp[] = {0,1,2,3};
	generate_actors(drawer, 4, temp);

	//GLenum flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
	//glGenBuffers(1, &drawer.ssbo);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, drawer.ssbo);
	//glBufferStorage(GL_SHADER_STORAGE_BUFFER, size, 0, flags);
	//drawer.vertices = (Vertex *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size, flags);
	generate_buffers(drawer);
}

void drawer_draw_combat(Drawer& drawer, Camera& camera, Vector2 team_positions[], short team_classes[], Vector2& cursor_pos, Uint32 *path)
{
	glUseProgram(drawer.the_one_shader);
	glUniform2fv(0, 1, &camera.position.x);
	glUniformMatrix4fv(1, 1, GL_FALSE, &camera.ortho.elements[0]);
	glUniform1i(2, (int)drawer.total_num_vertices);
	glUniform1i(3, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, drawer.the_one_texture.id);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, drawer.ssbo);

	glBindVertexArray(drawer.vao);
	glDrawElements(GL_TRIANGLES, drawer.total_num_indices, GL_UNSIGNED_SHORT, 0);
}

void drawer_draw_build(Drawer& drawer, Camera & camera, char* names[4])
{
	//Rect rect = rect_create(camera.position.x + 1280 / 2, camera.position.y + 720 / 2, 1280, 720);
	//SpriteAnimation anim;
	//anim.speed = 0.5f;
	//anim.sprite = rect_create(0, 0, 32, 32);
	//anim.size = rect_create(0, 0, 24 * 3, 32);
	//
	//float time = window_time_get();
	//glDisable(GL_DEPTH_TEST);
	//sprite_draw(&rect, &anim, &drawer.player_texture, time);
	//glEnable(GL_DEPTH_TEST);
}

void drawer_draw_mainmenu(Drawer & drawer, Camera & camera)
{

}

void generate_tilemap(Drawer& drawer, const Uint32* type_data, unsigned short height, unsigned short width, unsigned int tile_size_width, unsigned int tile_size_height)
{
	Quad rectangle_coordinates =
	{
		vector2_create(0.f, 0.f),
		vector2_create((float)tile_size_width, 0.f),
		vector2_create((float)tile_size_width, (float)tile_size_height),
		vector2_create(0.f, (float)tile_size_height)
	};

	unsigned short tilemap_vertices = 0;
	unsigned short tilemap_indices = 0;
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			Vector2 world_position = vector2_create((float)i * tile_size_width, (float)j * tile_size_height);

			drawer.sprites_world_positions[i + j * width] = world_position;

			drawer.vertex_local_coords[i + j * width][0] = rectangle_coordinates[0];
			drawer.vertex_local_coords[i + j * width][1] = rectangle_coordinates[1];
			drawer.vertex_local_coords[i + j * width][2] = rectangle_coordinates[2];
			drawer.vertex_local_coords[i + j * width][3] = rectangle_coordinates[3];

			for (int k = 0; k < 4; ++k)
			{
				drawer.vertex_colors[i + j * width + k].r = 255;
				drawer.vertex_colors[i + j * width + k].g = 0;
				drawer.vertex_colors[i + j * width + k].b = 0;
			}

			int tile_number = type_data[i + j * width] + 32*15; // 32*15 is to offset to the tiles in the one texture

			int uv_x = tile_number % (drawer.the_one_texture.width / tile_size_width);
			int uv_y = tile_number / (drawer.the_one_texture.width / tile_size_width);

			float gl_x = (float)uv_x / (drawer.the_one_texture.width / tile_size_width);
			float gl_y = (float)uv_y / (drawer.the_one_texture.height / tile_size_height);

			float tex_width = (float)tile_size_width / drawer.the_one_texture.width;
			float tex_height = (float)tile_size_height / drawer.the_one_texture.height;

			drawer.vertex_tex_coords[i + j * width][0] = vector2_create(gl_x, gl_y + tex_height);
			drawer.vertex_tex_coords[i + j * width][1] = vector2_create(gl_x + tex_width, gl_y + tex_height);
			drawer.vertex_tex_coords[i + j * width][2] = vector2_create(gl_x + tex_width, gl_y);
			drawer.vertex_tex_coords[i + j * width][3] = vector2_create(gl_x, gl_y);

			drawer.vertex_indices[tilemap_indices++] = tilemap_vertices + 0;
			drawer.vertex_indices[tilemap_indices++] = tilemap_vertices + 1;
			drawer.vertex_indices[tilemap_indices++] = tilemap_vertices + 2;
			drawer.vertex_indices[tilemap_indices++] = tilemap_vertices + 0;
			drawer.vertex_indices[tilemap_indices++] = tilemap_vertices + 2;
			drawer.vertex_indices[tilemap_indices++] = tilemap_vertices + 3;

			tilemap_vertices += 4;
		}
	}

	drawer.total_num_vertices += tilemap_vertices;
	drawer.total_num_indices += tilemap_indices;
}

void generate_actors(Drawer& drawer, int num_actors, unsigned short classes[])
{
	const int sprite_width = 32.f;
	const int sprite_height = 32.f;

	Quad rectangle_coordinates =
	{
		vector2_create(0.f, 0.f),
		vector2_create(sprite_width, 0.f),
		vector2_create(sprite_width, sprite_height),
		vector2_create(0.f, sprite_height)
	};
	
	for (int i = 0; i < num_actors; ++i)
	{
		drawer.sprites_world_positions[drawer.total_num_vertices/4] = vector2_create(-100,0);

		drawer.vertex_local_coords[drawer.total_num_vertices/4][0] = rectangle_coordinates[0];
		drawer.vertex_local_coords[drawer.total_num_vertices/4][1] = rectangle_coordinates[1];
		drawer.vertex_local_coords[drawer.total_num_vertices/4][2] = rectangle_coordinates[2];
		drawer.vertex_local_coords[drawer.total_num_vertices/4][3] = rectangle_coordinates[3];

		for (int k = 0; k < 4; ++k)
		{
			drawer.vertex_colors[drawer.total_num_vertices / 4+k].r = 255;
			drawer.vertex_colors[drawer.total_num_vertices / 4+k].g = 0;
			drawer.vertex_colors[drawer.total_num_vertices / 4+k].b = 0;
		}
	
		int tile_number = classes[i] * 4;
	
		int uv_x = tile_number % (drawer.the_one_texture.width / sprite_width);
		int uv_y = tile_number / (drawer.the_one_texture.width / sprite_width);
	
		float gl_x = (float)uv_x / (drawer.the_one_texture.width / sprite_width);
		float gl_y = (float)uv_y / (drawer.the_one_texture.height / sprite_height);
	
		float tex_width = (float)sprite_width / drawer.the_one_texture.width;
		float tex_height = (float)sprite_height / drawer.the_one_texture.height;
	
		drawer.vertex_tex_coords[drawer.total_num_vertices/4][0] = vector2_create(gl_x, gl_y + tex_height);
		drawer.vertex_tex_coords[drawer.total_num_vertices/4][1] = vector2_create(gl_x + tex_width, gl_y + tex_height);
		drawer.vertex_tex_coords[drawer.total_num_vertices/4][2] = vector2_create(gl_x + tex_width, gl_y);
		drawer.vertex_tex_coords[drawer.total_num_vertices/4][3] = vector2_create(gl_x, gl_y);

		drawer.vertex_indices[drawer.total_num_indices++] = drawer.total_num_vertices + 0;
		drawer.vertex_indices[drawer.total_num_indices++] = drawer.total_num_vertices + 1;
		drawer.vertex_indices[drawer.total_num_indices++] = drawer.total_num_vertices + 2;
		drawer.vertex_indices[drawer.total_num_indices++] = drawer.total_num_vertices + 0;
		drawer.vertex_indices[drawer.total_num_indices++] = drawer.total_num_vertices + 2;
		drawer.vertex_indices[drawer.total_num_indices++] = drawer.total_num_vertices + 3;
	
		drawer.total_num_vertices += 4;
	}
}

void generate_buffers(Drawer& drawer)
{
	glGenVertexArrays(1, &drawer.vao);
	glBindVertexArray(drawer.vao);
	glGenBuffers(1, &drawer.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, drawer.vbo);

	unsigned int size = sizeof(Vector2) * drawer.total_num_vertices;
	glBufferData(GL_ARRAY_BUFFER, size * 2 + drawer.total_num_vertices * sizeof(Color), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, &drawer.vertex_local_coords[0]);
	glBufferSubData(GL_ARRAY_BUFFER, size, size, &drawer.vertex_tex_coords[0]);
	glBufferSubData(GL_ARRAY_BUFFER, size*2, drawer.total_num_vertices * sizeof(Color), &drawer.vertex_colors[0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)(size));
	glVertexAttribPointer(2, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Color), (void*)(size * 2));

	glGenBuffers(1, &drawer.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawer.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * drawer.total_num_indices, &drawer.vertex_indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &drawer.ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, drawer.ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size / 4, &drawer.sprites_world_positions[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, drawer.ssbo);
}