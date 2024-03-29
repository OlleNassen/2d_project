#include "actor.h"

GameState * game_stack_push(GameStack *stack)
{
	GameState *src = &stack->data[stack->top];
	unsigned int new_top = (stack->top + 1) % 128;

	if (stack->bottom != stack->top)
	{	
		stack->top = new_top;
	}

	stack->data[stack->top] = *src;

	return &stack->data[stack->top];
}

GameState * game_stack_pop(GameStack *stack)
{
	unsigned int new_top = (stack->top - 1) % 128;

	if (new_top != stack->bottom)
	{
		stack->top = new_top;
	}
	return &stack->data[stack->top];
}

GameState * game_stack_peek(GameStack *stack)
{
	return &stack->data[stack->top];
}