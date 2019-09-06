#ifndef CAMERA_H
#define CAMERA_H
#include <math2d.h>

struct Camera
{
	mat4 ortho;
	Vector3 position;
};

void camera_initialize_default(Camera& camera);

#endif