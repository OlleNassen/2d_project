#include "texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture texture_from_memory(const char *buffer)
{
	Texture text;
	text.id = 0;
	return text;
}

Texture texture_from_file(const char *path)
{
	Texture text;
	glGenTextures(1, &text.id);
	glBindTexture(GL_TEXTURE_2D, text.id);

	stbi_set_flip_vertically_on_load(false);

	int num_components;

	unsigned char* data = stbi_load(path, &text.width, &text.height, &num_components, 4);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text.width,
			text.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}
	return text;
}