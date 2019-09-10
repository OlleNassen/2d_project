#ifndef GAME_H
#define GAME_H
#include "camera.h"
#include "drawer.h"

enum CharacterClass
{
	Fighter, Gunman, Demolitionist, Driver
};

typedef struct
{
	CharacterClass character_class;
	short class_proficiency;
	const char* name;
	Vector2 position;
}CharacterData;

typedef struct
{
	unsigned short num_tiles_rows;
	unsigned short num_tiles_columns;
	char* tiles;
}GameMap;

struct Game
{
	CharacterData player;
	Camera camera;
	Drawer drawer;
	GameMap map;
};

void game_initialize(Game& game);
void game_update(Game& game);
void game_draw(Game& game);

#endif