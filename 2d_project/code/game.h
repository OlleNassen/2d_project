#ifndef GAME_H
#define GAME_H
#include "camera.h"
#include "drawer.h"

enum State
{
	StateMainMenu, StateBuild, StateCombat
};

enum CharacterClass
{
	Fighter, Gunman, Demolitionist, Driver, NumClasses
};

typedef struct
{
	short character_classes[4];
	short class_proficiencies[4];
	char* names[4];
	Vector2 positions[4];
}PlayerTeamData;

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
	State current_state;
	Cursor cursor;
	PlayerTeamData team_data;
	Camera camera;
	Drawer drawer;
	GameMap map;
	char* names;
};

void game_initialize(Game& game);
void game_update(Game& game);
void game_draw(Game& game);

#endif