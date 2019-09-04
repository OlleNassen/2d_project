#ifndef MATH2D_H
#define MATH2D_H

struct Vector2
{
	float x;
	float y;
};

Vector2 vector2(float x, float y);

float vector2_dot(Vector2 v);
float vector2_length(Vector2 v);
Vector2 vector2_normalize(Vector2 v);
Vector2 vector2_ortho(Vector2 v);

Vector2 vector2_add(Vector2 a, Vector2 b);
Vector2 vector2_subtract(Vector2 a, Vector2 b);
Vector2 vector2_multiply(Vector2 a, Vector2 b);
Vector2 vector2_divide(Vector2 a, Vector2 b);

#endif
