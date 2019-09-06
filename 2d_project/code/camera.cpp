#include "camera.h"
#include "math2d.h"

void camera_initialize_default(Camera& camera)
{
	camera.ortho = mat4_create_ortho(0.0f, 1280.f, 0.0f, 720.f, -1.f, 1.f);
	camera.position = vector3_create(0,0,1);
}