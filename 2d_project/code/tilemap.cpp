#include "tilemap.h"
#include "glad/glad.h"
#include "math2d.h"

typedef Vector2 Tile[4];

void tilemap_draw(Tilemap& tilemap)
{
	glBindVertexArray(tilemap.vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tilemap.texture.id);
	glDrawElements(GL_TRIANGLES, tilemap.num_tiles_rows * tilemap.num_tiles_columns * 6, GL_UNSIGNED_SHORT, 0);
}

Vector2 screen_to_world(Vector2& v)
{
	return vector2_create((v.x + 2.0f*v.y) / 4.0f, (2.0f*v.y - v.x) / 4.0f);
}

Vector2 world_to_screen(Vector2& v)
{
	return vector2_create(2.0f*v.x - 2.0f*v.y, v.x + v.y);
}

void tilemap_generate(Tilemap& tilemap, const char* type_data, unsigned short num_tiles_rows, unsigned short num_tiles_columns, unsigned int tile_size_x, unsigned int tile_size_y)
{
	tilemap.texture = texture_from_file("iso_tiles.png");

	tilemap.num_tiles_rows = num_tiles_rows;
	tilemap.num_tiles_columns = num_tiles_columns;

	tilemap.tile_size_x = tile_size_x;
	tilemap.tile_size_y = tile_size_y;

	Tile rectangle_coordinates =
	{
		vector2_create(0.f, 0.f),
		vector2_create((float)tile_size_x, 0.f),
		vector2_create((float)tile_size_x, (float)tile_size_y),
		vector2_create(0.f, (float)tile_size_y)
	};

	glGenVertexArrays(1, &tilemap.vao);
	glBindVertexArray(tilemap.vao);
	glGenBuffers(1, &tilemap.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tilemap.vbo);

	Tile* vertex_positions = new Tile[tilemap.num_tiles_rows*tilemap.num_tiles_columns];
	Tile* vertex_tex_coords = new Tile[tilemap.num_tiles_rows*tilemap.num_tiles_columns];
	unsigned short* indices = new unsigned short[tilemap.num_tiles_rows * tilemap.num_tiles_columns * 6];

	unsigned short offsetVert = 0;
	unsigned short offset = 0;
	for (unsigned int i = 0; i < tilemap.num_tiles_columns; ++i)
	{
		for (unsigned int j = 0; j < tilemap.num_tiles_rows; ++j)
		{
			vertex_positions[i + j * tilemap.num_tiles_columns][0] = vector2_add(rectangle_coordinates[0], vector2_create((float)i * tile_size_x, (float)j * tile_size_y));
			vertex_positions[i + j * tilemap.num_tiles_columns][1] = vector2_add(rectangle_coordinates[1], vector2_create((float)i * tile_size_x, (float)j * tile_size_y));
			vertex_positions[i + j * tilemap.num_tiles_columns][2] = vector2_add(rectangle_coordinates[2], vector2_create((float)i * tile_size_x, (float)j * tile_size_y));
			vertex_positions[i + j * tilemap.num_tiles_columns][3] = vector2_add(rectangle_coordinates[3], vector2_create((float)i * tile_size_x, (float)j * tile_size_y));

			vertex_positions[i + j * tilemap.num_tiles_columns][0] = world_to_screen(vertex_positions[i + j * tilemap.num_tiles_columns][0]);
			vertex_positions[i + j * tilemap.num_tiles_columns][1] = world_to_screen(vertex_positions[i + j * tilemap.num_tiles_columns][1]);
			vertex_positions[i + j * tilemap.num_tiles_columns][2] = world_to_screen(vertex_positions[i + j * tilemap.num_tiles_columns][2]);
			vertex_positions[i + j * tilemap.num_tiles_columns][3] = world_to_screen(vertex_positions[i + j * tilemap.num_tiles_columns][3]);

			int tile_number = type_data[i + j * tilemap.num_tiles_columns];

			int uv_x = tile_number % (tilemap.texture.width / tile_size_x);
			int uv_y = tile_number / (tilemap.texture.width / tile_size_x);

			float gl_x = (float)uv_x / (tilemap.texture.width / tile_size_x);
			float gl_y = (float)uv_y / (tilemap.texture.height / tile_size_y);

			float width = (float)tile_size_x / tilemap.texture.width;
			float height = (float)tile_size_y / tilemap.texture.height;

			vertex_tex_coords[i + j * tilemap.num_tiles_columns][0] = vector2_create(gl_x, gl_y + height);
			vertex_tex_coords[i + j * tilemap.num_tiles_columns][1] = vector2_create(gl_x + width, gl_y + height);
			vertex_tex_coords[i + j * tilemap.num_tiles_columns][2] = vector2_create(gl_x + width, gl_y);
			vertex_tex_coords[i + j * tilemap.num_tiles_columns][3] = vector2_create(gl_x, gl_y);

			indices[offset++] = offsetVert + 0;
			indices[offset++] = offsetVert + 1;
			indices[offset++] = offsetVert + 2;
			indices[offset++] = offsetVert + 0;
			indices[offset++] = offsetVert + 2;
			indices[offset++] = offsetVert + 3;

			offsetVert += 4;
		}
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(Tile) * tilemap.num_tiles_rows * tilemap.num_tiles_columns * 2, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Tile) * tilemap.num_tiles_rows * tilemap.num_tiles_columns, &vertex_positions[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Tile) * tilemap.num_tiles_rows * tilemap.num_tiles_columns, sizeof(Tile) * tilemap.num_tiles_rows * tilemap.num_tiles_columns, &vertex_tex_coords[0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)(sizeof(Tile) * tilemap.num_tiles_rows * tilemap.num_tiles_columns));

	glGenBuffers(1, &tilemap.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tilemap.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * tilemap.num_tiles_rows * tilemap.num_tiles_columns * 6, &indices[0], GL_STATIC_DRAW);

	delete[] vertex_positions;
	delete[] vertex_tex_coords;
	delete[] indices;
}