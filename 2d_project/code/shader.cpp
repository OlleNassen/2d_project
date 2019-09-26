#include "shader.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

void memory_byte_set(void *destination, char source, int length)
{
	char *char_destination = (char *)destination;

	for (int i = 0; i < length; ++i)
	{
		char_destination[i] = source;
	}
}

char* read_entire_file(const char *path)
{
	FILE *file = fopen(path, "rb");
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);
	char *data = (char *)malloc(size + 1);
	memory_byte_set(data, 0, size + 1);
	fread(data, size, 1, file);
	return data;
}

unsigned int shader_create(char *shaderCode, unsigned int shaderType, const char *shaderString)
{
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, 0);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, 0, infoLog);

		printf(
			"ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n\n",
			shaderString, infoLog);
	}
	return shader;
}

unsigned int shader_program_create(const char *vertexPath, const char *fragmentPath)
{
	char *vertexCode = read_entire_file(vertexPath);
	char *fragmentCode = read_entire_file(fragmentPath);

	unsigned int vertex = shader_create(vertexCode, GL_VERTEX_SHADER, "VERTEX");
	unsigned int fragment = shader_create(fragmentCode, GL_FRAGMENT_SHADER, "FRAGMENT");

	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vertex);
	glAttachShader(shader, fragment);
	glLinkProgram(shader);

	int success;
	char infoLog[512];
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 512, 0, infoLog);

		printf(
			"ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM\n%s\n\n",
			infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	free(vertexCode);
	free(fragmentCode);

	return shader;
}