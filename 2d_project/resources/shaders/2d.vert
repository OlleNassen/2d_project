#version 330

layout(location = 0)in vec2 position;

out vec2 uv;

uniform vec2 view;
uniform mat4 projection;

void main()
{
	uv = position;
	gl_Position = projection * vec4(view + position, 0, 1);
}