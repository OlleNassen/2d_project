#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvcoord;

out vec2 uv;
out float z;

uniform int num_vertices;
uniform vec2 view;
uniform mat4 projection;

void main()
{
	uv = uvcoord;
	z = float(gl_VertexID) / float(num_vertices);
	gl_Position = projection * vec4(view + position, 0, 1);
}