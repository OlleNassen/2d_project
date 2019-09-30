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

struct SelectAction
{
	Action head;
	int x;
	int y;
	GameState *state;
};

static ActionResult select_execute(Action *action)
{
	SelectAction *select = (SelectAction *)action;

	for (int i = 0; i < 256; ++i)
	{
		if ((int)select->state->actors[i].x / 32 == select->x / 32 &&
			(int)select->state->actors[i].y / 32 == select->y / 32)
		{
			select->state->selected = i;
		}
	}
	
	return {};
}

static ActionResult select_undo(Action *action)
{
	SelectAction *select = (SelectAction *)action;
	select->state->selected = 0;
	return {};
}

struct MoveAction
{
	Action head;
	float x;
	float y;
	float oldx;
	float oldy;
	Actor *selected;
};

static ActionResult move_execute(Action *action)
{
	MoveAction *move = (MoveAction *)action;
	Actor *actor = move->selected;
	
	move->oldx = actor->x;
	move->oldy = actor->y;

	actor->x = move->x;
	actor->y = move->y;
	return {};
}

static ActionResult move_undo(Action *action)
{
	MoveAction *move = (MoveAction *)action;
	Actor *actor = move->selected;

	actor->x = move->oldx;
	actor->y = move->oldy;
	return {};
}

#endif
