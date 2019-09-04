#ifndef WINDOW_H
#define WINDOW_H
#include <SDL/SDL.h>

struct Window
{
	SDL_Window* window;
	SDL_GLContext glContext;
};

void windowInitialize(Window& window, const char* title, int width, int height);
void windowClear(float r, float g, float b, float alpha);
void windowDisplay(Window& window);

#endif