#ifndef CAMERA_H
#define CAMERA_H
#include "math2d.h"

typedef enum
{
	mov_none,
	mov_mouse_cursor,
	mov_mouse_buttons,
	mov_keyboard_keys,
	mov_gamepad_buttons
} CameraState;

struct Camera
{
	Mat4 ortho;
	Vector3 position;

	float speed;

	int mx;
	int my;

	unsigned int mouse_buttons[4];
	unsigned int keyboard_keys[4];
	unsigned int gamepad_buttons[4];

	CameraState state;
};

void camera_initialize_default(Camera& camera);

Vector2 camera_update(Camera *camera);

#endif