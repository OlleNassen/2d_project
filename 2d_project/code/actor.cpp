#include "actor.h"


Actor * actor_stack_push(ActorStack *stack)
{
	char *src = (char *)stack->top;
	stack->top += stack->num_actors;

	if (stack->top > (stack->actors + stack->max_actors))
	{	
		stack->top = 0;
	}

	char *dst = (char *)stack->top;

	for (unsigned int i = 0; i < stack->num_actors; ++i)
	{
		dst[i] = src[i];
	}

	return stack->top;
}

Actor * actor_stack_pop(ActorStack *stack)
{
	stack->top -= stack->num_actors;

	if (stack->top < stack->actors)
	{
		stack->top = (stack->actors + stack->max_actors) - stack->num_actors;
	}
	return stack->top;
}

Actor * actor_stack_peek(ActorStack *stack)
{
	return stack->top;
}