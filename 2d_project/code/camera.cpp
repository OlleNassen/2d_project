#include "camera.h"
#include "window.h"

void camera_initialize_default(Camera& camera)
{
	camera.ortho = mat4_create_ortho(0.0f, 1280.f, 0.0f, 720.f, -1.f, 1.f);
	camera.position = vector3_create(0,0,1);
}

Vector2 camera_update(Camera *camera)
{
	camera->state = mov_none;
	int mx = camera->mx;
	int my = camera->my;
	window_mouse_position(&mx, &my);

	if (mx != camera->mx || my != camera->my)
	{
		camera->state = mov_mouse_cursor;
	}

	GameButton up;
	GameButton down;
	GameButton left;
	GameButton right;

	if (camera->state == mov_none)
	{
		/*up = window_keyboard_pressed(camera->keyboard_keys[0]);
		down = window_keyboard_pressed(camera->keyboard_keys[1]);
		left = window_keyboard_pressed(camera->keyboard_keys[2]);
		right = window_keyboard_pressed(camera->keyboard_keys[3]);*/
		if (up.pressed || down.pressed || left.pressed || right.pressed)
		{
			camera->state = mov_mouse_buttons;
		}			
	}
	
	if (camera->state == mov_none)
	{
		up = window_keyboard_pressed(camera->keyboard_keys[0]);
		down = window_keyboard_pressed(camera->keyboard_keys[1]);
		left = window_keyboard_pressed(camera->keyboard_keys[2]);
		right = window_keyboard_pressed(camera->keyboard_keys[3]);
		if (up.pressed || down.pressed || left.pressed || right.pressed)
		{
			camera->state = mov_keyboard_keys;
		}
	}

	if (camera->state == mov_none)
	{
		up = window_keyboard_pressed(camera->keyboard_keys[0]);
		down = window_keyboard_pressed(camera->keyboard_keys[1]);
		left = window_keyboard_pressed(camera->keyboard_keys[2]);
		right = window_keyboard_pressed(camera->keyboard_keys[3]);
		if (up.pressed || down.pressed || left.pressed || right.pressed)
		{
			camera->state = mov_gamepad_buttons;
		}
	}

	if (camera->state != mov_mouse_cursor)
	{
		Vector2 direction = vector2_create(0.0f, 0.0f);
		if (up.pressed) direction.y += 1.0f;
		if (down.pressed) direction.y -= 1.0f;
		if (left.pressed) direction.y -= 1.0f;
		if (right.pressed) direction.y += 1.0f;
		
		camera->position.x += direction.x * camera->speed;
		camera->position.y += direction.y * camera->speed;
	}
	
}