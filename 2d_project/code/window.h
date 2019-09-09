#ifndef WINDOW_H
#define WINDOW_H

typedef unsigned int bool32;

typedef enum
{
	window_windowed,
	window_borderless,
	window_fullscreen
} WindowType;

typedef struct
{
	unsigned int transitions;
	bool32 pressed;
} GameButton;

void window_initialize(const char* title, int width, int height);

void window_events_poll();

double window_time_get();

GameButton window_keyboard_pressed(int key);
GameButton window_mouse_pressed(int button);
void window_mouse_position_set(int x, int y);
void window_mouse_position_get(int *x, int *y);
void window_cursor_visible(bool32 is_visible);

void window_size_set(int width, int height);
void window_size_get(int *width, int *height);

void window_type_set(WindowType type);

bool32 window_open();
void window_clear();
void window_display();

#endif