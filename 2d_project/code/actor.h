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

typedef struct
{
	Actor *actors;
	Actor *top;
	int max_actors;
	int num_actors;
} ActorStack;

Actor * actor_stack_push(ActorStack *stack);
Actor * actor_stack_pop(ActorStack *stack);
Actor * actor_stack_peek(ActorStack *stack);


#endif
