#version 330

layout(location = 0)in vec2 position;

out vec2 uv;

uniform vec2 view;
uniform mat4 projection;

void main()
{
	uv = position;
	gl_Position = projection * vec4(view.xy,0,0) + vec4(position.xy, 0, 1);
}