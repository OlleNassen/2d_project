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
	Actor actors[256];
} ActorPool;

typedef struct
{
	ActorPool data[128];
	int bottom;
	int top;
} ActorStack;

ActorPool * actor_stack_push(ActorStack *stack);
ActorPool * actor_stack_pop(ActorStack *stack);
ActorPool * actor_stack_peek(ActorStack *stack);


#endif
