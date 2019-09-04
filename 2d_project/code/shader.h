#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>

unsigned int shaderCreate(const char* vertexPath, const char* fragmentPath);
unsigned int shaderCreate(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
unsigned int shaderCreate(const char* computePath);

void shaderUniform(unsigned int shader, const char* name, bool value);
void shaderUniform(unsigned int shader, const char* name, char* value, int size);
void shaderUniform(unsigned int shader, const char* name, int value);
void shaderUniform(unsigned int shader, const char* name, float value);
void shaderUniform(unsigned int shader, const char* name, const glm::vec2& value);
void shaderUniform(unsigned int shader, const char* name, const glm::vec3& value);
void shaderUniform(unsigned int shader, const char* name, const glm::vec4& value);
void shaderUniform(unsigned int shader, const char* name, const glm::mat4& value);

#endif