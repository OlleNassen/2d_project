#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "math2d.h"

void camera_initialize_default(Camera& camera)
{
	camera.ortho = glm::ortho(0.f, 1280.f, 0.0f, 720.f);
	camera.position = glm::vec3(0,0,1);
}