#include "math2d.h"
#include <math.h>
#include <memory.h>

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

Vector2 vector2_scale(Vector2 a, float k)
{
	a.x *= k;
	a.y *= k;
	return a;
}

Vector3 vector3_create(float x, float y, float z)
{
	Vector3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

float vector3_dot(Vector3 v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float vector3_length(Vector3 v)
{
	return sqrtf(vector3_dot(v));
}

Vector3 vector3_normalize(Vector3 v)
{
	float length = vector3_length(v);
	v.x /= length;
	v.y /= length;
	v.z /= length;
	return v;
}

Vector3 vector3_cross(Vector3 a, Vector3 b)
{
	Vector3 v;
	v.x = a.y * b.z - a.z * b.y;
	v.y = a.x * b.z - a.z * b.x;
	v.z = a.x * b.y - a.y * b.x;
	return v;
}

Vector3 vector3_add(Vector3 a, Vector3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

Vector3 vector3_subtract(Vector3 a, Vector3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

Vector3 vector3_scale(Vector3 a, float k)
{
	a.x *= k;
	a.y *= k;
	a.z *= k;
	return a;
}

Mat4 mat4_create_identity()
{
	Mat4 m;
	memset(&m.elements[0], 0, sizeof(float) * 16);
	m.elements[0] = 1.f;
	m.elements[5] = 1.f;
	m.elements[10] = 1.f;
	m.elements[15] = 1.f;
	return m;
}

Mat4 mat4_create_ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	Mat4 m;
	memset(&m.elements[0], 0, sizeof(float) * 16);

	m.elements[0] = 2.f / (right - left);
	m.elements[5] = 2.f / (top - bottom);
	m.elements[10] = -2.f / (zFar - zNear);
	m.elements[12] = -(right + left) / (right - left);
	m.elements[13] = -(top + bottom) / (top - bottom);
	m.elements[14] = -(zFar + zNear) / (zFar - zNear);
	m.elements[15] = 1;
	return m;
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

Vector2 cart_to_dimetric(Vector2& v)
{
	return vector2_create(2.0f*v.x - 2.0f*v.y, v.x + v.y);
}

Vector2 dimetric_to_cart(Vector2& v)
{
	return vector2_create((v.x + 2.0f*v.y) / 4.0f, (2.0f*v.y - v.x) / 4.0f);
}
