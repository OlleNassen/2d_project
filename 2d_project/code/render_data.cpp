#include "render_data.h"
#include <glad/glad.h>
#include "math2d.h"

typedef Vector2 Tile[4];

void tilemap_draw(Tilemap& tilemap)
{
	glBindVertexArray(tilemap.vao);
	glDrawElements(GL_TRIANGLES, tilemap.num_tiles_rows * tilemap.num_tiles_columns * 6, GL_UNSIGNED_SHORT, 0);
}

void tilemap_generate(Tilemap& tilemap, const Uint32* type_data, unsigned int texture_width, unsigned int texture_height, unsigned short num_tiles_rows, unsigned short num_tiles_columns, unsigned int tile_size_x, unsigned int tile_size_y)
{
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
			Vector2 convert_positions = vector2_create((float)i * tile_size_x, (float)j * tile_size_y);
			convert_positions = cart_to_dimetric(convert_positions);

			vertex_positions[i + j * tilemap.num_tiles_columns][0] = vector2_add(vector2_scale(rectangle_coordinates[0], 4.0f), vector2_create(convert_positions.x, convert_positions.y));
			vertex_positions[i + j * tilemap.num_tiles_columns][1] = vector2_add(vector2_scale(rectangle_coordinates[1], 4.0f), vector2_create(convert_positions.x, convert_positions.y));
			vertex_positions[i + j * tilemap.num_tiles_columns][2] = vector2_add(vector2_scale(rectangle_coordinates[2], 4.0f), vector2_create(convert_positions.x, convert_positions.y));
			vertex_positions[i + j * tilemap.num_tiles_columns][3] = vector2_add(vector2_scale(rectangle_coordinates[3], 4.0f), vector2_create(convert_positions.x, convert_positions.y));

			int tile_number = type_data[i + j * tilemap.num_tiles_columns];

			int uv_x = tile_number % (texture_width / tile_size_x);
			int uv_y = tile_number / (texture_width / tile_size_x);

			float gl_x = (float)uv_x / (texture_width / tile_size_x);
			float gl_y = (float)uv_y / (texture_height / tile_size_y);

			float width = (float)tile_size_x / texture_width;
			float height = (float)tile_size_y / texture_height;

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

	tilemap.num_indices = offsetVert;

	delete[] vertex_positions;
	delete[] vertex_tex_coords;
	delete[] indices;
}

typedef struct
{
	float x;
	float y;
	float u;
	float v;
} SpriteVertex;

void sprite_draw(Rect *rect, SpriteAnimation *anim, Texture *text, float time)
{
	SpriteVertex vertices[4];
	vertices[0].x = rect->x + rect->w * 0.5f;
	vertices[0].y = rect->y - rect->h * 0.5f;

	vertices[1].x = rect->x - rect->w * 0.5f;
	vertices[1].y = rect->y - rect->h * 0.5f;

	vertices[2].x = rect->x + rect->w * 0.5f;
	vertices[2].y = rect->y + rect->h * 0.5f;

	vertices[3].x = rect->x - rect->w * 0.5f;
	vertices[3].y = rect->y + rect->h * 0.5f;

	int width = anim->size.w / anim->sprite.w;
	int height = anim->size.h / anim->sprite.h;
	int frame = (int)(time / anim->speed) % (width * height);

	int x = frame % width;
	int y = frame / width;

	Rect uv;
	uv.x = anim->sprite.x / text->width;
	uv.y = anim->sprite.y / text->height;
	uv.w = anim->sprite.w / text->width;
	uv.h = anim->sprite.h / text->height;

	vertices[0].u = x * uv.w + uv.x + uv.w;
	vertices[0].v = y * uv.h + uv.y + uv.h;

	vertices[1].u = x * uv.w + uv.x;
	vertices[1].v = y * uv.h + uv.y + uv.h;

	vertices[2].u = x * uv.w + uv.x + uv.w;
	vertices[2].v = y * uv.h + uv.y;

	vertices[3].u = x * uv.w + uv.x;
	vertices[3].v = y * uv.h + uv.y;

	/*vertices[0].u = anim->sprite.x + anim->sprite.w;
	vertices[0].v = anim->sprite.y;

	vertices[1].u = anim->sprite.x;
	vertices[1].v = anim->sprite.y;

	vertices[2].u = anim->sprite.x + anim->sprite.w;
	vertices[2].v = anim->sprite.y + anim->sprite.h;

	vertices[3].u = anim->sprite.x;
	vertices[3].v = anim->sprite.y + anim->sprite.h;*/

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, text->id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}