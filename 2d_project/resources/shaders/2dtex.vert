#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvcoord;

out vec2 uv;

uniform vec2 view;
uniform mat4 projection;

vec2 world_to_screen(vec2 v)
{
	return vec2(2.0f*v.x - 2.0f*v.y, v.x + v.y);
}

void main()
{
	uv = uvcoord;
	gl_Position = projection * vec4(view + position, 0, 1);
}