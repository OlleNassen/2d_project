#include "camera.h"
#include<glm/gtc/matrix_transform.hpp>
#include "math2d.h"

void cameraInitializeDefault(Camera& camera)
{
	camera.ortho = glm::ortho(0.f, 1280.f, 0.0f, 720.f);
	camera.position = glm::vec3(0,0,1);
}

glm::mat4 cameraGetViewMatrix(Camera& camera)
{
	static glm::vec3 forward(0,0,-1);
	static glm::vec3 up(0,1,0);
	return glm::lookAt(camera.position, camera.position + forward, up);
}