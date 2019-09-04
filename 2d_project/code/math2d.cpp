#include "math2d.h"
#include <math.h>

Vector2 vector2_create(float x, float y)
{
	Vector2 v;
	v.x = x;
	v.y = y;
	return v;
}

float vector2_dot(Vector2 v) 
{
	return v.x * v.x + v.y * v.y;
}

float vector2_length(Vector2 v)
{
	return sqrtf(vector2_dot(v));
}

Vector2 vector2_normalize(Vector2 v)
{
	float length = vector2_length(v);
	v.x = v.x / length;
	v.y = v.y / length;
	return v;
}

Vector2 vector2_ortho(Vector2 v)
{
	float y = -v.x;
	v.x = -v.y;
	v.y = y;
	return v;
}

Vector2 vector2_add(Vector2 a, Vector2 b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

Vector2 vector2_subtract(Vector2 a, Vector2 b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

Vector2 vector2_multiply(Vector2 a, Vector2 b)
{
	a.x *= b.x;
	a.y *= b.y;
	return a;
}

Vector2 vector2_divide(Vector2 a, Vector2 b)
{
	a.x /= b.x;
	a.y /= b.y;
	return a;
}



Rect rect_create(float x, float y, float w, float h)
{
	Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}

int rect_contains(Rect *r, float x, float y)
{
	if ((r->x - r->w) > x) return false;
	if ((r->y - r->h) > y) return false;
	if ((r->x + r->w) < x) return false;
	if ((r->y + r->h) < y) return false;

	return true;
}