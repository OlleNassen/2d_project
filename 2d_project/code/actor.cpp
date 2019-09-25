#include "actor.h"


ActorPool * actor_stack_push(ActorStack *stack)
{
	ActorPool *src = &stack->data[stack->top];
	unsigned int new_top = (stack->top + 1) % 128;

	if (stack->bottom != stack->top)
	{	
		stack->top = new_top;
	}

	ActorPool *dst = &stack->data[stack->top];

	for (unsigned int i = 0; i < 128; ++i)
	{
		dst[i] = src[i];
	}

	return &stack->data[stack->top];
}

ActorPool * actor_stack_pop(ActorStack *stack)
{
	unsigned int new_top = (stack->top - 1) % 128;

	if (new_top != stack->bottom)
	{
		stack->top = new_top;
	}
	return &stack->data[stack->top];
}

ActorPool * actor_stack_peek(ActorStack *stack)
{
	return &stack->data[stack->top];
}