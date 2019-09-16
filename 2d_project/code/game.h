#ifndef GAME_H
#define GAME_H
#include "camera.h"
#include "drawer.h"

enum CharacterClass
{
	Fighter, Gunman, Demolitionist, Driver, NumClasses
};

typedef struct
{
	CharacterClass character_class;
	short class_proficiency;
	char* name;
	Vector2 position;
}CharacterData;

typedef struct
{
	unsigned short num_tiles_rows;
	unsigned short num_tiles_columns;
	char* tiles;
}GameMap;

typedef struct
{
	Vector2 position;
}Cursor;

struct Game
{
	Cursor cursor;
	CharacterData player;
	Camera camera;
	Drawer drawer;
	GameMap map;
	char* names;
};

void game_initialize(Game& game);
void game_update(Game& game);
void game_draw(Game& game);

#endif