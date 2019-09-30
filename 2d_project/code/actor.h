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

struct Action;

struct ActionResult
{
	bool succeded;
	Action *alternative;
};

struct Action
{
	ActionResult(*execute)(struct Action *);
	ActionResult(*undo)(struct Action *);
};

struct Actor2
{
	int energy;
	Action *next_action;
};

static Actor2 actors[128];
static int current_actor;

static void process()
{
	Action *action = actors[current_actor].next_action;
	ActionResult result = action->execute(action);

	while (result.succeded && result.alternative)
	{
		result = action->execute(action);
		action = result.alternative;
	}

	if (result.succeded)
	{
		current_actor = (current_actor + 1) % 128;
	}

}


struct MoveAction
{
	Action head;

	float direction;
};

static void move_action(Action *action)
{
	MoveAction *move = (MoveAction *)action;
}

struct SelectAction
{
	Action head;
	GameState *state;
};

static ActionResult select_execute(Action *action)
{
	SelectAction *select = (SelectAction *)action;
	select->state->selected = 1;
	return {};
}

static ActionResult select_undo(Action *action)
{
	SelectAction *select = (SelectAction *)action;
	select->state->selected = 0;
	return {};
}

#endif
