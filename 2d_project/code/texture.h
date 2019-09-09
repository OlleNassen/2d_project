#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct
{
	unsigned int id;
	int width;
	int height;
} Texture;


Texture texture_from_memory(const char *buffer);
Texture texture_from_file(const char *path);

#endif