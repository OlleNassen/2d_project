#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

struct Camera
{
	glm::mat4 ortho;
	glm::vec3 position;
};

void cameraInitializeDefault(Camera& camera);
glm::mat4 cameraGetViewMatrix(Camera& camera);

#endif