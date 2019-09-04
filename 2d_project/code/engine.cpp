#include "engine.h"
#include "window.h"
#include "game.h"

void engineRun()
{
	window_initialize("Royale", 1280, 720);
	
	Game game;
	gameInitialize(game);
	gameStart(game);

	double lastTime = window_time_get();
	double deltaTime = 0.0;
	bool running = true;
	while (window_open())
	{
		window_time_get();
		double now = window_time_get();
		deltaTime = now - lastTime;
		lastTime = now;

		window_events_poll();

		gameUpdate(game);

		window_clear();
		gameRender(game);
		window_display();
	}

}
