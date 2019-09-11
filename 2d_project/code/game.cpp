#include "game.h"
#include "window.h"
#include <SDL/SDL.h>
#include <memory.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PI 3.14159

void create_game_map(GameMap& gameMap);
void generate_character(CharacterData& character);

void game_initialize(Game& game)
{
	create_game_map(game.map);
	camera_initialize_default(game.camera);
	drawer_initialize(game.drawer, game.map.tiles, game.map.num_tiles_rows, game.map.num_tiles_columns);
	generate_character(game.player);
	game.player.position.x = 32 * 4;
	game.player.position.y = 32 * 4;
	srand(time(0));
}

void game_update(Game& game)
{
	camera_update(&game.camera);

	static int stupid_frame_timer = 0;

	if (stupid_frame_timer >= 60)
	{
		if (window_keyboard_pressed(SDLK_i).pressed)
		{
			game.player.position.y = game.player.position.y + 32;
			stupid_frame_timer = 0;
		}
		if (window_keyboard_pressed(SDLK_j).pressed)
		{
			game.player.position.x = game.player.position.x - 32;
			stupid_frame_timer = 0;
		}
		if (window_keyboard_pressed(SDLK_k).pressed)
		{
			game.player.position.y = game.player.position.y - 32;
			stupid_frame_timer = 0;
		}
		if (window_keyboard_pressed(SDLK_l).pressed)
		{
			game.player.position.x = game.player.position.x + 32;
			stupid_frame_timer = 0;
		}
	}

	if (window_mouse_pressed(SDL_BUTTON_LEFT).pressed)
	{
		int x, y;
		window_mouse_position(&x, &y);
		float conv_x = (2.0f * x) / 1280.f - 1.0f;
		float conv_y = 1.0f - (2.0f * y) / 720.f;
		Vector2 ray_nds = vector2_create(conv_x, conv_y);
		Vector2 inv = vector2_create(game.camera.ortho.elements[12], game.camera.ortho.elements[13]);

		Mat4 m = game.camera.ortho;

		m.elements[12] = m.elements[3];
		m.elements[13] = m.elements[7];

		ray_nds.x += m.elements[12];
		ray_nds.y += m.elements[13];

		ray_nds.x -= game.camera.position.x;
		ray_nds.y -= game.camera.position.y;

		Vector2 selected_pos = vector2_create(ray_nds.x, ray_nds.y);
		//selected_pos = cart_to_dimetric(selected_pos);
		int selected_tile = game.map.tiles[(int)selected_pos.y + (int)selected_pos.x * game.map.num_tiles_columns];

		game.player.position.x = (int)selected_pos.x;
		game.player.position.y = (int)selected_pos.y;
	}

	stupid_frame_timer++;
}

void game_draw(Game& game)
{
	drawer_draw(game.drawer, game.camera, &game.player.position, 1);
}

void create_game_map(GameMap& gameMap)
{
	gameMap.num_tiles_rows = 40;
	gameMap.num_tiles_columns = 60;
	gameMap.tiles = new char[gameMap.num_tiles_rows * gameMap.num_tiles_columns];
	for (int i = 0; i < gameMap.num_tiles_rows * gameMap.num_tiles_columns; ++i)
	{
		int row = rand() % 7;
		row *= 9;
		row += rand() % 6;

		gameMap.tiles[i] = row;
	}
}

void generate_character(CharacterData& character)
{
	FILE* f;
	char temp[7];
	temp[6] = 0;

	fopen_s(&f, "names.bin", "r");
	fread(temp, sizeof(char), 6, f);
	fclose(f);

	printf(temp);
}