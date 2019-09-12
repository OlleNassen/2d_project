#include "engine.h"
#include "window.h"
#include "game.h"
#include <SDL/SDL.h>

typedef enum
{

} GameState;

void game_update(GameState state, Game *game)
{
	switch (state)
	{
	default: game_update(*game); break;
	}
}

void engine_run()
{
	window_initialize("Royale", 1280, 720);
	
	Game game;
	game_initialize(game);

	double last_time = window_time_get();
	double delta_time = 0.0;
	bool running = true;
	while (running)
	{
		window_time_get();
		double now = window_time_get();
		delta_time = now - last_time;
		last_time = now;

		window_events_poll();

		game_update(game);

		window_clear();
		game_draw(game);
		window_display();

		GameButton escape = window_keyboard_pressed(SDLK_ESCAPE);
		running = running && !escape.pressed;
	}

}
