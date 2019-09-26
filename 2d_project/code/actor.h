#ifndef ACTOR_H
#define ACTOR_H

typedef enum 
{

} ActorType;
typedef struct
{
	ActorType type;
	float x;
	float y;
	union 
	{
		float f;
		int i;
	};
} Actor;

#include "math2d.h" 
typedef struct
{
	Rect rect;

} Peice;

typedef struct
{

} Inventory;

typedef struct
{
	unsigned int selected;
	Actor actors[256];
} GameState;

typedef struct
{
	GameState data[128];
	unsigned int bottom;
	unsigned int top;
} GameStack;

GameState * game_stack_push(GameStack *stack);
GameState * game_stack_pop(GameStack *stack);
GameState * game_stack_peek(GameStack *stack);

static bool can_push_state(GameState *state)
{
	if (state->selected != 0)
	{
		return true;
	}
	return false;
}

#endif
