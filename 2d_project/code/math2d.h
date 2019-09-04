#ifndef MATH2D_H
#define MATH2D_H

typedef struct
{
	float x;
	float y;
} Vector2;

Vector2 vector2_create(float x, float y);

float vector2_dot(Vector2 v);
float vector2_length(Vector2 v);
Vector2 vector2_normalize(Vector2 v);
Vector2 vector2_ortho(Vector2 v);

Vector2 vector2_add(Vector2 a, Vector2 b);
Vector2 vector2_subtract(Vector2 a, Vector2 b);
Vector2 vector2_multiply(Vector2 a, Vector2 b);
Vector2 vector2_divide(Vector2 a, Vector2 b);

typedef struct
{
	float x;
	float y;
	float w;
	float h;
} Rect;

Rect rect_create(float x, float y, float w, float h);
int rect_contains(Rect *r, float x, float y);

#endif
