#version 440

layout(location = 0) in vec2 uvcoord;

layout(std430, binding = 3) buffer world_positions
{
    vec2 positions[];
};

out vec2 uv;
out float z;

uniform int num_vertices;
uniform vec2 view;
uniform mat4 projection;

vec2 cart_to_dimetric(vec2 v)
{
	return vec2(2.0f*v.x - 2.0f*v.y, v.x + v.y);
}

void main()
{
	uv = vec2(uvcoord.x, uvcoord.y);
	z = float(gl_VertexID) / float(num_vertices);

	vec2 local_coords[6];

	local_coords[0]	= vec2(0.0,0.0);
	local_coords[1]	= vec2(32.0,0.0);
	local_coords[2]	= vec2(32.0,32.0);
	local_coords[3]	= vec2(0.0,32.0);

	vec2 position = 4*local_coords[gl_VertexID % 4] + cart_to_dimetric(positions[gl_VertexID]);

	gl_Position = projection * vec4(view + position, 0, 1);
}