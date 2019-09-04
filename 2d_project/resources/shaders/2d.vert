#version 330

layout(location = 0)in vec2 position;

out vec2 uv;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	uv = position;
	gl_Position = projection * view * vec4(position.xy, 0, 1);
}