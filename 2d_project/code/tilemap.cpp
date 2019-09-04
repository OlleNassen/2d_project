#include "tilemap.h"
#include "glad/glad.h"
#include "math2d.h"

typedef Vector2 Tile[4];

void tilemap_draw(Tilemap & tilemap)
{
	glBindVertexArray(tilemap.vao);
	glDrawElements(GL_TRIANGLES, tilemap.num_tiles_x * tilemap.num_tiles_y * 6, GL_UNSIGNED_SHORT, 0);
}

void tilemap_generate(Tilemap& tilemap, unsigned int num_tiles_x, unsigned int num_tiles_y, unsigned int tile_size_x, unsigned int tile_size_y)
{
	tilemap.num_tiles_x = num_tiles_x;
	tilemap.num_tiles_y = num_tiles_y;

	tilemap.tile_size_x = tile_size_x;
	tilemap.tile_size_y = tile_size_y;

	Tile rect =
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

	Tile* vertex_data = new Tile[num_tiles_x*num_tiles_y];
	//Stilemap.type = new char[num_tiles_x * num_tiles_y];
	unsigned short* indices = new unsigned short[num_tiles_x * num_tiles_y * 6];

	unsigned short offsetVert = 0;
	unsigned short offset = 0;
	for (unsigned int i = 0; i < num_tiles_y; ++i)
	{
		for (unsigned int j = 0; j < num_tiles_x; ++j)
		{
			//tilemap.type[i+j*num_tiles_x] = 'a';
			vertex_data[i + j * num_tiles_y][0] = vector2_add(rect[0], vector2_create(j * tile_size_x, i * tile_size_y));
			vertex_data[i + j * num_tiles_y][1] = vector2_add(rect[1], vector2_create(j * tile_size_x, i * tile_size_y));
			vertex_data[i + j * num_tiles_y][2] = vector2_add(rect[2], vector2_create(j * tile_size_x, i * tile_size_y));
			vertex_data[i + j * num_tiles_y][3] = vector2_add(rect[3], vector2_create(j * tile_size_x, i * tile_size_y));

			indices[offset++] = offsetVert + 0;
			indices[offset++] = offsetVert + 1;
			indices[offset++] = offsetVert + 2;
			indices[offset++] = offsetVert + 0;
			indices[offset++] = offsetVert + 2;
			indices[offset++] = offsetVert + 3;

			offsetVert += 4;
		}
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(Tile) * num_tiles_x * num_tiles_y, &vertex_data[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glGenBuffers(1, &tilemap.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tilemap.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * num_tiles_x * num_tiles_y * 6, &indices[0], GL_STATIC_DRAW);

	delete[] indices;
	delete[] vertex_data;
}