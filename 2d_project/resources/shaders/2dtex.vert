#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvcoord;

out vec2 uv;
out float z;

uniform vec2 view;
uniform mat4 projection;

void main()
{
	uv = uvcoord;

	z = 1.0 - 1.0/gl_VertexID;
	if(gl_VertexID == 0)
		z = 0.0;
	gl_Position = projection * vec4(view + position, 0, 1);
}