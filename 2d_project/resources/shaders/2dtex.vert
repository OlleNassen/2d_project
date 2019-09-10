#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvcoord;

out vec2 uv;

uniform vec2 view;
uniform mat4 projection;

void main()
{
	uv = vec2(uvcoord.x, -uvcoord.y);
	gl_Position = projection * vec4(view + position, 0, 1);
}