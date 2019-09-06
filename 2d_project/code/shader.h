#ifndef SHADER_H
#define SHADER_H
#include "math2d.h"

unsigned int shader_create(const char* vertexPath, const char* fragmentPath);
unsigned int shader_create(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
unsigned int shader_create(const char* computePath);

void shader_uniform(unsigned int shader, const char* name, bool value);
void shader_uniform(unsigned int shader, const char* name, char* value, int size);
void shader_uniform(unsigned int shader, const char* name, int value);
void shader_uniform(unsigned int shader, const char* name, float value);
void shader_uniform(unsigned int shader, const char* name, const Vector2& value);
void shader_uniform(unsigned int shader, const char* name, const Vector3& value);
void shader_uniform(unsigned int shader, const char* name, const Mat4& value);

#endif