#include "engine.h"
#include "window.h"
#include "game.h"

void engineRun()
{
	window_initialize("Royale", 1280, 720);
	
	Game game;
	game_initialize(game);
	game_start(game);

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

		game_update(game);

		window_clear();
		game_render(game);
		window_display();
	}

}
