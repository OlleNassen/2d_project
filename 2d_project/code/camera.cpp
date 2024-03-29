#include "camera.h"
#include "window.h"
#include <SDL/SDL.h>
#include <stdio.h>

void camera_initialize_default(Camera& camera)
{
	camera.ortho = mat4_create_ortho(0.0f, 1280.f, 0.0f, 720.f, -1.f, 1.f);
	camera.position = vector3_create(0,0,1);

	for (int i = 0; i < 4; ++i)
	{
		camera.mouse_buttons[i] = 0;
		camera.keyboard_keys[i] = 0;
		camera.gamepad_buttons[i] = 0;
	}
	camera.keyboard_keys[0] = SDLK_w;
	camera.keyboard_keys[1] = SDLK_s;
	camera.keyboard_keys[2] = SDLK_a;
	camera.keyboard_keys[3] = SDLK_d;
	camera.speed = 10.0f;
}

Vector2 camera_update(Camera *camera)
{
	camera->state = mov_none;
	int mx = camera->mx;
	int my = camera->my;
	window_mouse_position(&mx, &my);
	Vector2 direction = vector2_create(0.0f, 0.0f);

	if (mx != camera->mx || my != camera->my)
	{	
		window_cursor_visible(true);
		camera->state = mov_mouse_cursor;
	}

	GameButton up = {};
	GameButton down = {};
	GameButton left = {};
	GameButton right = {};

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
			window_cursor_visible(false);
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


	int width = 0;
	int height = 0;
	window_size_get(&width, &height);
	int edgex = width * 0.05f;
	int edgey = height * 0.05f;

	camera->mx = mx;
	camera->my = my;

	if (my < edgey) direction.y -= 1.0f;
	if (my > height - edgey) direction.y += 1.0f;
	if (mx < edgex) direction.x += 1.0f;
	if (mx > width - edgex) direction.x -= 1.0f;

	if (up.pressed) direction.y -= 1.0f;
	if (down.pressed) direction.y += 1.0f;
	if (left.pressed) direction.x += 1.0f;
	if (right.pressed) direction.x -= 1.0f;

	camera->position.x += direction.x * camera->speed;
	camera->position.y += direction.y * camera->speed;

	return vector2_create(0, 0);
}