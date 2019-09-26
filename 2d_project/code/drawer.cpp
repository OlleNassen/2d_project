#include "drawer.h"
#include "shader.h"
#include <glad/glad.h>
#include "window.h"

void generate_tilemap(Drawer& drawer, const Uint32* type_data, unsigned int texture_width, unsigned int texture_height, unsigned short height, unsigned short width, unsigned int tile_size_width, unsigned int tile_size_height);
void generate_actors(Drawer& drawer, int num_actors);
void generate_buffers(Drawer& drawer);

void drawer_initialize(Drawer& drawer, const Uint32* type_data, unsigned short num_tiles_rows, unsigned short num_tiles_columns)
{
	drawer.shader = shader_program_create("resources/shaders/2dtex.vert", "resources/shaders/2dtex.frag");

	drawer.tilemap_texture = texture_from_file("tiles.png");
	drawer.cursor_texture = texture_from_file("cursor.png");
	drawer.player_texture = texture_from_file("spritesheet.png");

	unsigned int size = 1024 * 1024;
	drawer.sprites_world_positions = new Vector2[size];
	drawer.vertex_local_coords = new Quad[size];
	drawer.vertex_tex_coords = new Quad[size];
	drawer.vertex_indices = new unsigned short[size * 6];
	drawer.total_num_indices = 0;
	drawer.total_num_vertices = 0;

	generate_tilemap(drawer, type_data, drawer.tilemap_texture.width, drawer.tilemap_texture.height, num_tiles_rows, num_tiles_columns, 32, 32);

	GLenum flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
	glGenBuffers(1, &drawer.sprite_storage);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, drawer.sprite_storage);
	glBufferStorage(GL_SHADER_STORAGE_BUFFER, size, 0, flags);
	drawer.vertices = (Vertex *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size, flags);
	generate_buffers(drawer);
}

void drawer_draw_combat(Drawer& drawer, Camera& camera, Vector2 team_positions[], short team_classes[], Vector2& cursor_pos, Uint32 *path)
{
	glUseProgram(drawer.shader);
	glUniform2fv(0, 1, &vector2_create(camera.position.x, camera.position.y).x);
	glUniformMatrix4fv(1, 1, GL_FALSE, &camera.ortho.elements[0]);
	glUniform1i(2, (int)drawer.total_num_vertices);
	glUniform1i(3, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, drawer.tilemap_texture.id);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, drawer.ssbo);

	glBindVertexArray(drawer.vao);
	glDrawElements(GL_TRIANGLES, drawer.total_num_indices, GL_UNSIGNED_SHORT, 0);
}

void drawer_draw_build(Drawer& drawer, Camera & camera, char* names[4])
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

void generate_tilemap(Drawer& drawer, const Uint32* type_data, unsigned int texture_width, unsigned int texture_height, unsigned short height, unsigned short width, unsigned int tile_size_width, unsigned int tile_size_height)
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

			int tile_number = type_data[i + j * width];

			int uv_x = tile_number % (texture_width / tile_size_width);
			int uv_y = tile_number / (texture_width / tile_size_width);

			float gl_x = (float)uv_x / (texture_width / tile_size_width);
			float gl_y = (float)uv_y / (texture_height / tile_size_height);

			float tex_width = (float)tile_size_width / texture_width;
			float tex_height = (float)tile_size_height / texture_height;

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

void generate_actors(Drawer& drawer, int num_actors)
{
	//Quad rectangle_coordinates =
	//{
	//	vector2_create(0.f, 0.f),
	//	vector2_create((float)tile_size_width, 0.f),
	//	vector2_create((float)tile_size_width, (float)tile_size_height),
	//	vector2_create(0.f, (float)tile_size_height)
	//};
	//
	//for (int i = 0; i < num_actors; ++i)
	//{
	//
	//}
}

void generate_buffers(Drawer& drawer)
{
	glGenVertexArrays(1, &drawer.vao);
	glBindVertexArray(drawer.vao);
	glGenBuffers(1, &drawer.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, drawer.vbo);

	unsigned int size = sizeof(Vector2) * drawer.total_num_vertices;
	glBufferData(GL_ARRAY_BUFFER, size * 2, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, &drawer.vertex_local_coords[0]);
	glBufferSubData(GL_ARRAY_BUFFER, size, size, &drawer.vertex_tex_coords[0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)(size));

	glGenBuffers(1, &drawer.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawer.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * drawer.total_num_indices, &drawer.vertex_indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &drawer.ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, drawer.ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size / 4, &drawer.sprites_world_positions[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, drawer.ssbo);
}