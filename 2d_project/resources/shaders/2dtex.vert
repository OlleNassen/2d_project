#version 440

layout(location = 0) in vec2 local_pos;
layout(location = 1) in vec2 uvcoord;
layout(location = 2) in vec3 vertex_color;

layout(std430, binding = 3) buffer world_positions
{
    vec2 positions[];
};

out vec2 uv;
out vec3 color;
out float z;

layout (location = 0) uniform vec2 view;
layout (location = 1) uniform mat4 projection;
layout (location = 2) uniform int num_vertices;

vec2 cart_to_dimetric(vec2 v)
{
	return vec2(2.0f*v.x - 2.0f*v.y, v.x + v.y);
}

void main()
{
	uv = uvcoord;
	color = vertex_color;
	z = float(gl_VertexID) / float(num_vertices);

	vec2 position = 4*local_pos + cart_to_dimetric(positions[gl_VertexID / 4]);

	gl_Position = projection * vec4(view + position, 0, 1);
}