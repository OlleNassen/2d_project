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
Vector2 vector2_scale(Vector2 a, float k);

typedef struct
{
	float x;
	float y;
	float z;
}Vector3;

Vector3 vector3_create(float x, float y, float z);

float vector3_dot(Vector3 v);
float vector3_length(Vector3 v);
Vector3 vector3_normalize(Vector3 v);
Vector3 vector3_cross(Vector3 a, Vector3 b);
	  
Vector3 vector3_add(Vector3 a, Vector3 b);
Vector3 vector3_subtract(Vector3 a, Vector3 b);
Vector3 vector3_scale(Vector3 a, float k);

typedef struct
{
	float elements[4*4];
}Mat4;

Mat4 mat4_create_identity();
Mat4 mat4_create_ortho(float left, float right, float bottom, float top, float zNear, float zFar);

typedef struct
{
	float x;
	float y;
	float w;
	float h;
} Rect;

Rect rect_create(float x, float y, float w, float h);
Rect rect_createfv(Vector2 v, float w, float h);
int rect_contains(Rect *r, float x, float y);

Vector2 cart_to_dimetric(Vector2 v);
Vector2 dimetric_to_cart(Vector2 v);

#endif
