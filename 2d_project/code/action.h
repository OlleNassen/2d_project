#ifndef ACTION_H
#define ACTION_H

#include "actor.h"

enum ActionType
{
	ActionTypeNone,
	ActionTypeSelect,
	ActionTypeMove,
	ActionTypeAttack
};

struct SelectAction
{
	int x;
	int y;
	GameState *state;
};

struct MoveAction
{
	float x;
	float y;
	float oldx;
	float oldy;
	unsigned old_mov;
	Actor *selected;
	unsigned *path;
	unsigned width;
	unsigned height;
};

struct AttackAction
{

};

struct Action
{
	enum ActionType type;
	union
	{
		struct SelectAction select;
		struct MoveAction move;
		struct AttackAction attack;
	};
};

static void select_perform(struct SelectAction *action);
static void move_perform(struct MoveAction *action);
static void attack_perform(struct AttackAction *action);

static void select_undo(struct SelectAction *action);
static void move_undo(struct MoveAction *action);
static void attack_undo(struct AttackAction *action);

void action_perform(Action *action)
{
	switch (action->type)
	{
	case ActionTypeSelect: { select_perform(&action->select); break; }
	case ActionTypeMove: { move_perform(&action->move); break; }
	case ActionTypeAttack: { attack_perform(&action->attack); break; }
	}
}

void action_undo(Action *action)
{
	switch (action->type)
	{
	case ActionTypeSelect: { select_undo(&action->select); break; }
	case ActionTypeMove: { move_undo(&action->move); break; }
	case ActionTypeAttack: { attack_undo(&action->attack); break; }
	}
}

static void select_perform(SelectAction *action)
{
	for (int i = 0; i < 256; ++i)
	{
		if ((int)action->state->actors[i].x / 32 == action->x / 32 &&
			(int)action->state->actors[i].y / 32 == action->y / 32)
		{
			action->state->selected = i;
		}
	}
}

static void move_perform(MoveAction *action)
{
	Actor *actor = action->selected;

	action->oldx = actor->x;
	action->oldy = actor->y;
	action->old_mov = actor->num_mov;

	int x = action->x / 32;
	int y = action->y / 32;

	if (x < action->width && y < action->height)
	{
		unsigned cost = action->path[x + y * action->width];
		if (cost < actor->num_mov)
		{
			actor->num_mov -= cost - 1;
			actor->x = action->x;
			actor->y = action->y;
		}


	}
}

static void attack_perform(AttackAction *action)
{

}



static void select_undo(SelectAction *action)
{
	action->state->selected = 0;
}

static void move_undo(MoveAction *action)
{
	Actor *actor = action->selected;

	actor->x = action->oldx;
	actor->y = action->oldy;
	actor->num_mov = action->old_mov;
}

static void attack_undo(AttackAction *action)
{

}

#endif
