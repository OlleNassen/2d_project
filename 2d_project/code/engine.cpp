#include "engine.h"
#include "window.h"
#include "game.h"

void engineRun()
{
	Window window;
	windowInitialize(window, "Royale", 1280, 720);
	Game game;
	gameInitialize(game);
	gameStart(game);

	double lastTime = (double)SDL_GetTicks() / 1000.0;
	double deltaTime = 0.0;
	bool running = true;
	while (running)
	{
		double now = (double)SDL_GetTicks() / 1000.0;
		deltaTime = now - lastTime;
		lastTime = now;

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
				{
					running = false;
					break;
				}

				case SDL_KEYDOWN:
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
						running = false;
					break;
			}
		}

		gameUpdate(game);

		windowClear(0,0,0, 1.0f);
		gameRender(game);
		windowDisplay(window);
	}

}
