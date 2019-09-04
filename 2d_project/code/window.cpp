#include "window.h"
#include <SDL/SDL.h>
#include <glad.c>

struct Window
{
	SDL_Window* window;
	SDL_GLContext glContext;
	bool32 window_open;
	double time;
	bool32 key_pressed[128];
};

static Window window;

void window_initialize(const char* title, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window.time = 0.0;
	window.window_open = true;
	
	window.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);

	if (!window.window)
	{
		printf("Unable to create window\n");
		printf("SLD Error : %s\n", SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	window.glContext = SDL_GL_CreateContext(window.window);

	SDL_GL_SetSwapInterval(1);
	SDL_SetRelativeMouseMode(SDL_TRUE);


	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("Failed to initialize GLAD");
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void window_events_poll()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
		{
			window.window_open = false;
			break;
		}

		case SDL_KEYDOWN:
		{
			if (e.key.keysym.sym < 128)
			{
				window.key_pressed[e.key.keysym.sym] = true;
			}	
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				window.window_open = false;
			break;
		}
		case SDL_KEYUP:
		{
			if (e.key.keysym.sym < 128)
			{
				window.key_pressed[e.key.keysym.sym] = false;
			}
			break;
		}
		}
	}
}

double window_time_get()
{
	return (double)SDL_GetTicks() / 1000.0;
}

bool32 window_keyboard_pressed(int key)
{
	return window.key_pressed[key];
}

bool32 window_mouse_pressed(int button)
{
	return 0;
}

void window_mouse_position(int *x, int *y)
{
	SDL_GetMouseState(x, y);
}

void window_size_set(int width, int height)
{
	SDL_SetWindowSize(window.window, width, height);
}

void window_size_get(int *width, int *height)
{
	SDL_GetWindowSize(window.window, width, height);
}

void window_type_set(WindowType type)
{
	switch (type)
	{
	case window_windowed:
	{
		SDL_SetWindowBordered(window.window, SDL_TRUE);
	}
	case window_borderless:
	{
		SDL_SetWindowBordered(window.window, SDL_FALSE);
	}
	case window_fullscreen:
	{
		SDL_SetWindowFullscreen(window.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	default:
	{

	}
	}
}

bool32 window_open()
{
	return window.window_open;
}

void window_clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void window_display()
{
	SDL_GL_SwapWindow(window.window);
}
